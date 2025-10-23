/*#include "awr_interface.h"
#include <iostream>

AWRInterface::AWRInterface(CircuitElements* circuit)
    : m_pAWRApp(nullptr)
    , m_pProject(nullptr)
    , m_pSchematic(nullptr)
    , m_pLastElement(nullptr)
    , m_bInitialized(false) 
    , m_portSchematic(nullptr)
    , m_port2Schematic(nullptr)
{
    circuitElements = circuit;
}

AWRInterface::~AWRInterface() {
    Cleanup();
}

bool AWRInterface::Initialize()
{
    HRESULT hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    if (FAILED(hr)) {
        qDebug() << "Failed to initialize COM: 0x"<<hr;
        return false;
    }

    CLSID clsid;
    hr = CLSIDFromProgID(L"MWOApp.MWOffice", &clsid);
    if (FAILED(hr)) {
        qDebug() << "Failed to get CLSID for MWOffice.Application: 0x";
        qDebug() << "Trying alternative ProgIDs...";

        // Пробуем альтернативные имена
        const wchar_t* alternatives[] = {
            L"AWR.Application",
            L"AWRDE.Application",
            L"MicrowaveOffice.Application"
        };

        bool found = false;
        for (const auto& progId : alternatives) {
            hr = CLSIDFromProgID(progId, &clsid);
            if (SUCCEEDED(hr)) {
                qDebug() << L"Found alternative ProgID: " << progId;
                found = true;
                break;
            }
        }

        if (!found) {
            qDebug() << "Make sure AWR Microwave Office is installed";
            CoUninitialize();
            return false;
        }
    }

    // Сначала пробуем подключиться к уже запущенному экземпляру
    qDebug() << "Trying to connect to running AWR instance...";
    IUnknown* pUnk = nullptr;
    hr = GetActiveObject(clsid, nullptr, &pUnk);

    if (SUCCEEDED(hr)) {
        hr = pUnk->QueryInterface(IID_IDispatch, (void**)&m_pAWRApp);
        pUnk->Release();

        if (SUCCEEDED(hr)) {
            qDebug() << "Connected to existing AWR instance";
            m_bInitialized = true;
            return true;
        }
    }

    // Если не нашли запущенный, создаём новый
    qDebug() << "Creating new AWR instance...";
    hr = CoCreateInstance(clsid, nullptr, CLSCTX_LOCAL_SERVER,
        IID_IDispatch, (void**)&m_pAWRApp);
    if (FAILED(hr)) {
        qDebug() << "Failed to create AWR instance: 0x";
        CoUninitialize();
        return false;
    }

    // Делаем окно видимым
    VARIANT visible;
    visible.vt = VT_BOOL;
    visible.boolVal = VARIANT_TRUE;
    SetProperty(m_pAWRApp, L"Visible", &visible);

    // Даём время на инициализацию
    Sleep(2000);

    m_bInitialized = true;
    qDebug() << "AWR interface initialized successfully";
    return true;
}

void AWRInterface::Cleanup()
{
    if (m_pLastElement) {
        m_pLastElement->Release();
        m_pLastElement = nullptr;
    }
    if (m_pSchematic) {
        m_pSchematic->Release();
        m_pSchematic = nullptr;
    }
    if (m_pProject) {
        m_pProject->Release();
        m_pProject = nullptr;
    }
    if (m_pAWRApp) {
        m_pAWRApp->Release();
        m_pAWRApp = nullptr;
    }

    if (m_bInitialized) {
        CoUninitialize();
        m_bInitialized = false;
    }
}

bool AWRInterface::CreateProject(const std::wstring& projectName)
{
    if (!m_bInitialized) {
        qDebug() << "AWR not initialized";
        return false;
    }

    qDebug() << "Attempting to call New_Project...";

    // Пробуем разные варианты создания проекта

    // Вариант 1: New_Project без параметров
    VARIANT result;
    VariantInit(&result);
    HRESULT hr = InvokeMethod(m_pAWRApp, L"New_Project", &result, DISPATCH_METHOD);

    qDebug() << "New_Project returned: 0x"<<hr;
    if (result.vt != VT_EMPTY) {
        qDebug() << "Result variant type: ";
    }

    // Независимо от результата, пробуем получить проект
    VARIANT projectVar;
    VariantInit(&projectVar);

    // Пробуем свойство Project
    qDebug()<<"Trying to get Project property...";
    hr = GetProperty(m_pAWRApp, L"Project", &projectVar);
    qDebug() << "GetProperty(Project) returned: 0x"<<hr;

    if (SUCCEEDED(hr) && projectVar.vt == VT_DISPATCH && projectVar.pdispVal != nullptr) {
        m_pProject = projectVar.pdispVal;
        qDebug() << "Project obtained successfully via Project property";
        return true;
    }

    // Пробуем свойство Projects (коллекция)
    qDebug() << "Trying to get Projects collection...";
    VARIANT projectsVar;
    VariantInit(&projectsVar);
    hr = GetProperty(m_pAWRApp, L"Projects", &projectsVar);
    qDebug() << "GetProperty(Projects) returned: 0x"<<hr;

    if (SUCCEEDED(hr) && projectsVar.vt == VT_DISPATCH && projectsVar.pdispVal != nullptr) {
        // Получаем количество проектов
        VARIANT countVar;
        VariantInit(&countVar);
        hr = GetProperty(projectsVar.pdispVal, L"Count", &countVar);

        if (SUCCEEDED(hr)) {
            long count = (countVar.vt == VT_I4) ? countVar.lVal : 0;
            qDebug() << "Projects count: "<<count;

            if (count > 0) {
                // Получаем первый проект через Item(1)
                DISPPARAMS params;
                VARIANT args[1];
                args[0].vt = VT_I4;
                args[0].lVal = 1;

                params.rgvarg = args;
                params.cArgs = 1;
                params.rgdispidNamedArgs = nullptr;
                params.cNamedArgs = 0;

                VARIANT itemResult;
                VariantInit(&itemResult);
                hr = InvokeMethod(projectsVar.pdispVal, L"Item", &itemResult, DISPATCH_METHOD, &params);

                if (SUCCEEDED(hr) && itemResult.vt == VT_DISPATCH && itemResult.pdispVal != nullptr) {
                    m_pProject = itemResult.pdispVal;
                    projectsVar.pdispVal->Release();
                    qDebug() << "Project obtained successfully via Projects(1)";
                    return true;
                }
            }
        }
        projectsVar.pdispVal->Release();
    }

    qDebug() << "Failed to obtain project object through all methods";
    return false;
}

bool AWRInterface::ClearAllElements()
{
    if (!m_pSchematic) return false;

    HRESULT hr;
    DISPID dispid;

    // Получаем коллекцию Elements
    OLECHAR* propElements = L"Elements";
    hr = m_pSchematic->GetIDsOfNames(IID_NULL, &propElements, 1,
        LOCALE_USER_DEFAULT, &dispid);
    if (FAILED(hr)) return false;

    DISPPARAMS noParams = { NULL, NULL, 0, 0 };
    VARIANT varElements;
    VariantInit(&varElements);

    hr = m_pSchematic->Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT,
        DISPATCH_PROPERTYGET, &noParams,
        &varElements, NULL, NULL);
    if (FAILED(hr) || varElements.vt != VT_DISPATCH) {
        VariantClear(&varElements);
        return false;
    }

    IDispatch* pElements = varElements.pdispVal;

    // Вызываем метод Clear() или RemoveAll()
    OLECHAR* methodClear = L"Clear";
    hr = pElements->GetIDsOfNames(IID_NULL, &methodClear, 1,
        LOCALE_USER_DEFAULT, &dispid);

    if (FAILED(hr)) {
        // Если Clear не найден, пробуем RemoveAll
        methodClear = L"RemoveAll";
        hr = pElements->GetIDsOfNames(IID_NULL, &methodClear, 1,
            LOCALE_USER_DEFAULT, &dispid);
    }

    if (SUCCEEDED(hr)) {
        VARIANT varResult;
        VariantInit(&varResult);

        hr = pElements->Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT,
            DISPATCH_METHOD, &noParams,
            &varResult, NULL, NULL);

        VariantClear(&varResult);
    }

    pElements->Release();
    VariantClear(&varElements);

    return SUCCEEDED(hr);
}

bool AWRInterface::ClearAllPortElements(bool end)
{
    if (end)
    {
        if (!m_port2Schematic) return false;
    }
    else
    {
        if (!m_portSchematic) return false;
    }
    HRESULT hr;
    DISPID dispid;
    OLECHAR* propElements = L"Elements";
    if (end)
    {
        hr = m_port2Schematic->GetIDsOfNames(IID_NULL, &propElements, 1,
            LOCALE_USER_DEFAULT, &dispid);
    }
    else
    {
        hr = m_portSchematic->GetIDsOfNames(IID_NULL, &propElements, 1,
            LOCALE_USER_DEFAULT, &dispid);
    }

   
   
    if (FAILED(hr)) return false;

    DISPPARAMS noParams = { NULL, NULL, 0, 0 };
    VARIANT varElements;
    VariantInit(&varElements);

    if (end)
    {
        hr = m_port2Schematic->Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT,
            DISPATCH_PROPERTYGET, &noParams,
            &varElements, NULL, NULL);
    }
    else
    {
        hr = m_portSchematic->Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT,
            DISPATCH_PROPERTYGET, &noParams,
            &varElements, NULL, NULL);
    }
    
    if (FAILED(hr) || varElements.vt != VT_DISPATCH) {
        VariantClear(&varElements);
        return false;
    }

    IDispatch* pElements = varElements.pdispVal;

    // Вызываем метод Clear() или RemoveAll()
    OLECHAR* methodClear = L"Clear";
    hr = pElements->GetIDsOfNames(IID_NULL, &methodClear, 1,
        LOCALE_USER_DEFAULT, &dispid);

    if (FAILED(hr)) {
        // Если Clear не найден, пробуем RemoveAll
        methodClear = L"RemoveAll";
        hr = pElements->GetIDsOfNames(IID_NULL, &methodClear, 1,
            LOCALE_USER_DEFAULT, &dispid);
    }

    if (SUCCEEDED(hr)) {
        VARIANT varResult;
        VariantInit(&varResult);

        hr = pElements->Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT,
            DISPATCH_METHOD, &noParams,
            &varResult, NULL, NULL);

        VariantClear(&varResult);
    }

    pElements->Release();
    VariantClear(&varElements);

    return SUCCEEDED(hr);
}

// Метод для удаления всех проводов
bool AWRInterface::ClearAllWires()
{
    if (!m_pSchematic) return false;

    HRESULT hr;
    DISPID dispid;

    // Получаем коллекцию Wires
    OLECHAR* propWires = L"Wires";
    hr = m_pSchematic->GetIDsOfNames(IID_NULL, &propWires, 1,
        LOCALE_USER_DEFAULT, &dispid);
    if (FAILED(hr)) return false;

    DISPPARAMS noParams = { NULL, NULL, 0, 0 };
    VARIANT varWires;
    VariantInit(&varWires);

    hr = m_pSchematic->Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT,
        DISPATCH_PROPERTYGET, &noParams,
        &varWires, NULL, NULL);
    if (FAILED(hr) || varWires.vt != VT_DISPATCH) {
        VariantClear(&varWires);
        return false;
    }

    IDispatch* pWires = varWires.pdispVal;

    // Вызываем Clear()
    OLECHAR* methodClear = L"Clear";
    hr = pWires->GetIDsOfNames(IID_NULL, &methodClear, 1,
        LOCALE_USER_DEFAULT, &dispid);

    if (FAILED(hr)) {
        methodClear = L"RemoveAll";
        hr = pWires->GetIDsOfNames(IID_NULL, &methodClear, 1,
            LOCALE_USER_DEFAULT, &dispid);
    }

    if (SUCCEEDED(hr)) {
        VARIANT varResult;
        VariantInit(&varResult);

        hr = pWires->Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT,
            DISPATCH_METHOD, &noParams,
            &varResult, NULL, NULL);

        VariantClear(&varResult);
    }

    pWires->Release();
    VariantClear(&varWires);

    return SUCCEEDED(hr);
}

bool AWRInterface::AddSchematic(const std::wstring& schematicName)
{
    if (!m_pProject) return false;

    // Получаем коллекцию Schematics
    VARIANT schematics;
    VariantInit(&schematics);

    HRESULT hr = GetProperty(m_pProject, L"Schematics", &schematics);
    if (FAILED(hr)) return false;

    // Добавляем новую схему
    VARIANT result;
    VariantInit(&result);

    DISPPARAMS params;
    VARIANT args[1];
    args[0].vt = VT_BSTR;
    args[0].bstrVal = SysAllocString(schematicName.c_str());

    params.rgvarg = args;
    params.cArgs = 1;
    params.rgdispidNamedArgs = nullptr;
    params.cNamedArgs = 0;

    hr = InvokeMethod(schematics.pdispVal, L"Add", &result, DISPATCH_METHOD, &params);

    SysFreeString(args[0].bstrVal);
    schematics.pdispVal->Release();

    if (SUCCEEDED(hr)) {
        m_pSchematic = result.pdispVal;
        return true;
    }

    return false;
}

bool AWRInterface::AddPortSchematic(const std::wstring& schematicName, bool end)
{
    if (!m_pProject) return false;

    // Получаем коллекцию Schematics
    VARIANT schematics;
    VariantInit(&schematics);

    HRESULT hr = GetProperty(m_pProject, L"Schematics", &schematics);
    if (FAILED(hr)) return false;

    // Добавляем новую схему
    VARIANT result;
    VariantInit(&result);

    DISPPARAMS params;
    VARIANT args[1];
    args[0].vt = VT_BSTR;
    args[0].bstrVal = SysAllocString(schematicName.c_str());

    params.rgvarg = args;
    params.cArgs = 1;
    params.rgdispidNamedArgs = nullptr;
    params.cNamedArgs = 0;

    hr = InvokeMethod(schematics.pdispVal, L"Add", &result, DISPATCH_METHOD, &params);

    SysFreeString(args[0].bstrVal);
    schematics.pdispVal->Release();

    if (SUCCEEDED(hr)) {
        if (end)
        {
            m_port2Schematic = result.pdispVal;
        }
        else
        {
            m_portSchematic = result.pdispVal;
        }
        return true;
    }

    return false;
}

bool AWRInterface::AddElement(const std::wstring& elementType, double x, double y, double angle)
{
    if (!m_pSchematic) return false;

    // Получаем коллекцию Elements
    VARIANT elements;
    VariantInit(&elements);

    HRESULT hr = GetProperty(m_pSchematic, L"Elements", &elements);
    if (FAILED(hr) || elements.vt != VT_DISPATCH) {
        qDebug() << "Failed to get Elements collection: 0x" <<hr;

        // Пробуем альтернативные имена
        hr = GetProperty(m_pSchematic, L"Schematic_Elements", &elements);
        if (FAILED(hr)) {
            qDebug() << "Also tried Schematic_Elements, failed";
            return false;
        }
    }

    qDebug() << L"Adding element of type: " << elementType;

    // Метод Add принимает 4 параметра: Type, X, Y, Rotation
    // Add(Type As String, X As Long, Y As Long, Rotation As Long) As Element
    VARIANT result;
    VariantInit(&result);

    DISPPARAMS params;
    VARIANT args[4];

    // Параметры идут в обратном порядке!
    // args[3] = Type (string)
    // args[2] = X (long)
    // args[1] = Y (long) 
    // args[0] = Rotation (long)

    args[3].vt = VT_BSTR;
    args[3].bstrVal = SysAllocString(elementType.c_str());

    args[2].vt = VT_I4;
    args[2].lVal = static_cast<long>(x);

    args[1].vt = VT_I4;
    args[1].lVal = static_cast<long>(y);

    args[0].vt = VT_I4;
    args[0].lVal = static_cast<long>(angle);  // rotation angle in degrees

    params.rgvarg = args;
    params.cArgs = 4;
    params.rgdispidNamedArgs = nullptr;
    params.cNamedArgs = 0;

    hr = InvokeMethod(elements.pdispVal, L"Add", &result, DISPATCH_METHOD, &params);

    SysFreeString(args[3].bstrVal);

    if (FAILED(hr)) {
        qDebug() << "Failed to add element: 0x"<< hr;
        elements.pdispVal->Release();
        return false;
    }

    if (result.vt != VT_DISPATCH || result.pdispVal == nullptr) {
        qDebug() << "Element not returned (VT=" << result.vt << ")";
        elements.pdispVal->Release();
        return false;
    }

    if (m_pLastElement) m_pLastElement->Release();
    m_pLastElement = result.pdispVal;
    elements.pdispVal->Release();

    qDebug() << "Element " << elementType
        << " added successfully at (" << x << ", " << y << ")";
    return true;
}

bool AWRInterface::AddPortElement(const std::wstring& elementType, double x, double y, double angle, bool end)
{
    if (end)
    {
        if (!m_port2Schematic) return false;
    }
    else
    {
        if (!m_portSchematic) return false;
    }

    // Получаем коллекцию Elements
    VARIANT elements;
    VariantInit(&elements);
    HRESULT hr;
    if (end)
    {
        hr = GetProperty(m_port2Schematic, L"Elements", &elements);
    }
    else
    {
        hr = GetProperty(m_portSchematic, L"Elements", &elements);
    }
    
    if (FAILED(hr) || elements.vt != VT_DISPATCH) {
        qDebug() << "Failed to get Elements collection: 0x" << hr;

        if (end)
        {
            hr = GetProperty(m_port2Schematic, L"Schematic_Elements", &elements);
        }
        else
        {
            hr = GetProperty(m_portSchematic, L"Schematic_Elements", &elements);
        }
        // Пробуем альтернативные имена
        hr = GetProperty(m_portSchematic, L"Schematic_Elements", &elements);
        if (FAILED(hr)) {
            qDebug() << "Also tried Schematic_Elements, failed";
            return false;
        }
    }

    qDebug() << L"Adding element of type: " << elementType;

    // Метод Add принимает 4 параметра: Type, X, Y, Rotation
    // Add(Type As String, X As Long, Y As Long, Rotation As Long) As Element
    VARIANT result;
    VariantInit(&result);

    DISPPARAMS params;
    VARIANT args[4];

    // Параметры идут в обратном порядке!
    // args[3] = Type (string)
    // args[2] = X (long)
    // args[1] = Y (long) 
    // args[0] = Rotation (long)

    args[3].vt = VT_BSTR;
    args[3].bstrVal = SysAllocString(elementType.c_str());

    args[2].vt = VT_I4;
    args[2].lVal = static_cast<long>(x);

    args[1].vt = VT_I4;
    args[1].lVal = static_cast<long>(y);

    args[0].vt = VT_I4;
    args[0].lVal = static_cast<long>(angle);  // rotation angle in degrees

    params.rgvarg = args;
    params.cArgs = 4;
    params.rgdispidNamedArgs = nullptr;
    params.cNamedArgs = 0;

    hr = InvokeMethod(elements.pdispVal, L"Add", &result, DISPATCH_METHOD, &params);

    SysFreeString(args[3].bstrVal);

    if (FAILED(hr)) {
        qDebug() << "Failed to add element: 0x" << hr;
        elements.pdispVal->Release();
        return false;
    }

    if (result.vt != VT_DISPATCH || result.pdispVal == nullptr) {
        qDebug() << "Element not returned (VT=" << result.vt << ")";
        elements.pdispVal->Release();
        return false;
    }

    if (m_pLastElement) m_pLastElement->Release();
    m_pLastElement = result.pdispVal;
    elements.pdispVal->Release();

    qDebug() << "Element " << elementType
        << " added successfully at (" << x << ", " << y << ")";
    return true;
}

bool AWRInterface::AddWire(double x1, double y1, double x2, double y2)
{
    if (!m_pSchematic) return false;

    HRESULT hr;
    DISPID dispid;

    // 1. Получаем коллекцию Wires
    OLECHAR* propWires = L"Wires";
    hr = m_pSchematic->GetIDsOfNames(IID_NULL, &propWires, 1,
        LOCALE_USER_DEFAULT, &dispid);
    if (FAILED(hr)) return false;

    DISPPARAMS noParams = { NULL, NULL, 0, 0 };
    VARIANT varWires;
    VariantInit(&varWires);

    hr = m_pSchematic->Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT,
        DISPATCH_PROPERTYGET, &noParams,
        &varWires, NULL, NULL);
    if (FAILED(hr) || varWires.vt != VT_DISPATCH) {
        VariantClear(&varWires);
        return false;
    }

    IDispatch* pWires = varWires.pdispVal;

    // 2. Вызываем метод Add для добавления провода
    OLECHAR* methodAdd = L"Add";
    hr = pWires->GetIDsOfNames(IID_NULL, &methodAdd, 1,
        LOCALE_USER_DEFAULT, &dispid);
    if (FAILED(hr)) {
        pWires->Release();
        VariantClear(&varWires);
        return false;
    }

    // 3. Подготавливаем аргументы: x1, y1, x2, y2
    // ВАЖНО: аргументы в обратном порядке!
    VARIANT args[4];
    VariantInit(&args[0]);
    VariantInit(&args[1]);
    VariantInit(&args[2]);
    VariantInit(&args[3]);

    args[3].vt = VT_R8;  // x1
    args[3].dblVal = x1;

    args[2].vt = VT_R8;  // y1
    args[2].dblVal = y1;

    args[1].vt = VT_R8;  // x2
    args[1].dblVal = x2;

    args[0].vt = VT_R8;  // y2
    args[0].dblVal = y2;

    DISPPARAMS addParams;
    addParams.rgvarg = args;
    addParams.cArgs = 4;
    addParams.rgdispidNamedArgs = NULL;
    addParams.cNamedArgs = 0;

    VARIANT varWire;
    VariantInit(&varWire);

    hr = pWires->Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT,
        DISPATCH_METHOD, &addParams,
        &varWire, NULL, NULL);

    // Очистка
    pWires->Release();
    VariantClear(&varWires);
    VariantClear(&varWire);

    return SUCCEEDED(hr);
}

bool AWRInterface::SetFrequencySweep(double startFreq, double stopFreq, int numPoints)
{
    if (!m_pProject) return false;

    HRESULT hr;
    DISPID dispid;

    // 1. Получаем объект Frequencies
    OLECHAR* propFrequencies = L"Frequencies";
    hr = m_pProject->GetIDsOfNames(IID_NULL, &propFrequencies, 1,
        LOCALE_USER_DEFAULT, &dispid);
    if (FAILED(hr)) return false;

    DISPPARAMS noParams = { NULL, NULL, 0, 0 };
    VARIANT varFreqs;
    VariantInit(&varFreqs);

    hr = m_pProject->Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT,
        DISPATCH_PROPERTYGET, &noParams,
        &varFreqs, NULL, NULL);
    if (FAILED(hr) || varFreqs.vt != VT_DISPATCH) {
        VariantClear(&varFreqs);
        return false;
    }

    IDispatch* pFrequencies = varFreqs.pdispVal;

    // 2. Устанавливаем начальную частоту (Start)
    OLECHAR* propStart = L"Start";
    hr = pFrequencies->GetIDsOfNames(IID_NULL, &propStart, 1,
        LOCALE_USER_DEFAULT, &dispid);
    if (SUCCEEDED(hr)) {
        VARIANT varStart;
        VariantInit(&varStart);
        varStart.vt = VT_R8;
        varStart.dblVal = startFreq;

        DISPID dispidNamed = DISPID_PROPERTYPUT;
        DISPPARAMS startParams;
        startParams.rgvarg = &varStart;
        startParams.cArgs = 1;
        startParams.rgdispidNamedArgs = &dispidNamed;
        startParams.cNamedArgs = 1;

        VARIANT varResult;
        VariantInit(&varResult);

        hr = pFrequencies->Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT,
            DISPATCH_PROPERTYPUT, &startParams,
            &varResult, NULL, NULL);

        VariantClear(&varStart);
        VariantClear(&varResult);
    }

    // 3. Устанавливаем конечную частоту (Stop)
    OLECHAR* propStop = L"Stop";
    hr = pFrequencies->GetIDsOfNames(IID_NULL, &propStop, 1,
        LOCALE_USER_DEFAULT, &dispid);
    if (SUCCEEDED(hr)) {
        VARIANT varStop;
        VariantInit(&varStop);
        varStop.vt = VT_R8;
        varStop.dblVal = stopFreq;

        DISPID dispidNamed = DISPID_PROPERTYPUT;
        DISPPARAMS stopParams;
        stopParams.rgvarg = &varStop;
        stopParams.cArgs = 1;
        stopParams.rgdispidNamedArgs = &dispidNamed;
        stopParams.cNamedArgs = 1;

        VARIANT varResult;
        VariantInit(&varResult);

        hr = pFrequencies->Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT,
            DISPATCH_PROPERTYPUT, &stopParams,
            &varResult, NULL, NULL);

        VariantClear(&varStop);
        VariantClear(&varResult);
    }

    // 4. Устанавливаем количество точек (NumPts)
    OLECHAR* propNumPts = L"NumPts";
    hr = pFrequencies->GetIDsOfNames(IID_NULL, &propNumPts, 1,
        LOCALE_USER_DEFAULT, &dispid);
    if (SUCCEEDED(hr)) {
        VARIANT varNumPts;
        VariantInit(&varNumPts);
        varNumPts.vt = VT_I4;
        varNumPts.lVal = numPoints;

        DISPID dispidNamed = DISPID_PROPERTYPUT;
        DISPPARAMS numPtsParams;
        numPtsParams.rgvarg = &varNumPts;
        numPtsParams.cArgs = 1;
        numPtsParams.rgdispidNamedArgs = &dispidNamed;
        numPtsParams.cNamedArgs = 1;

        VARIANT varResult;
        VariantInit(&varResult);

        hr = pFrequencies->Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT,
            DISPATCH_PROPERTYPUT, &numPtsParams,
            &varResult, NULL, NULL);

        VariantClear(&varNumPts);
        VariantClear(&varResult);
    }

    pFrequencies->Release();
    VariantClear(&varFreqs);

    return true;
}

// Альтернативный метод - установка одной рабочей частоты
bool AWRInterface::SetSingleFrequency(double frequency)
{
    // Устанавливаем узкий диапазон вокруг одной частоты
    return SetFrequencySweep(frequency, frequency, 1);
}

// Метод для установки типа развёртки (линейная/логарифмическая)
bool AWRInterface::SetSweepType(bool isLinear)
{
    if (!m_pProject) return false;

    HRESULT hr;
    DISPID dispid;

    OLECHAR* propFrequencies = L"Frequencies";
    hr = m_pProject->GetIDsOfNames(IID_NULL, &propFrequencies, 1,
        LOCALE_USER_DEFAULT, &dispid);
    if (FAILED(hr)) return false;

    DISPPARAMS noParams = { NULL, NULL, 0, 0 };
    VARIANT varFreqs;
    VariantInit(&varFreqs);

    hr = m_pProject->Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT,
        DISPATCH_PROPERTYGET, &noParams,
        &varFreqs, NULL, NULL);
    if (FAILED(hr)) {
        VariantClear(&varFreqs);
        return false;
    }

    IDispatch* pFrequencies = varFreqs.pdispVal;

    // Устанавливаем тип развёртки (SweepType)
    // 0 = Linear, 1 = Log, 2 = Single
    OLECHAR* propSweepType = L"SweepType";
    hr = pFrequencies->GetIDsOfNames(IID_NULL, &propSweepType, 1,
        LOCALE_USER_DEFAULT, &dispid);
    if (SUCCEEDED(hr)) {
        VARIANT varType;
        VariantInit(&varType);
        varType.vt = VT_I4;
        varType.lVal = isLinear ? 0 : 1;  // 0=Linear, 1=Log

        DISPID dispidNamed = DISPID_PROPERTYPUT;
        DISPPARAMS typeParams;
        typeParams.rgvarg = &varType;
        typeParams.cArgs = 1;
        typeParams.rgdispidNamedArgs = &dispidNamed;
        typeParams.cNamedArgs = 1;

        VARIANT varResult;
        VariantInit(&varResult);

        hr = pFrequencies->Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT,
            DISPATCH_PROPERTYPUT, &typeParams,
            &varResult, NULL, NULL);

        VariantClear(&varType);
        VariantClear(&varResult);
    }

    pFrequencies->Release();
    VariantClear(&varFreqs);

    return SUCCEEDED(hr);
}


bool AWRInterface::SetElementParameter(const wchar_t* paramName, const wchar_t* value)
{
    if (!m_pLastElement || !paramName || !value) return false;

    HRESULT hr;
    VARIANT varResult;
    DISPID dispid;

    // 1. Получаем коллекцию Parameters
    OLECHAR* propParameters = L"Parameters";
    hr = m_pLastElement->GetIDsOfNames(IID_NULL, &propParameters, 1,
        LOCALE_USER_DEFAULT, &dispid);
    if (FAILED(hr)) return false;

    DISPPARAMS noParams = { NULL, NULL, 0, 0 };
    VariantInit(&varResult);

    hr = m_pLastElement->Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT,
        DISPATCH_PROPERTYGET, &noParams,
        &varResult, NULL, NULL);
    if (FAILED(hr) || varResult.vt != VT_DISPATCH) {
        VariantClear(&varResult);
        return false;
    }

    IDispatch* pParameters = varResult.pdispVal;

    // 2. Получаем конкретный параметр по имени через Item
    OLECHAR* methodItem = L"Item";
    hr = pParameters->GetIDsOfNames(IID_NULL, &methodItem, 1,
        LOCALE_USER_DEFAULT, &dispid);
    if (FAILED(hr)) {
        pParameters->Release();
        VariantClear(&varResult);
        return false;
    }

    // Подготавливаем аргумент - имя параметра
    VARIANT varParamName;
    VariantInit(&varParamName);
    varParamName.vt = VT_BSTR;
    varParamName.bstrVal = SysAllocString(paramName);

    DISPPARAMS itemParams;
    itemParams.rgvarg = &varParamName;
    itemParams.cArgs = 1;
    itemParams.rgdispidNamedArgs = NULL;
    itemParams.cNamedArgs = 0;

    VARIANT varParam;
    VariantInit(&varParam);

    hr = pParameters->Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT,
        DISPATCH_PROPERTYGET, &itemParams,
        &varParam, NULL, NULL);

    pParameters->Release();
    VariantClear(&varParamName);
    VariantClear(&varResult);

    if (FAILED(hr) || varParam.vt != VT_DISPATCH) {
        VariantClear(&varParam);
        return false;
    }

    IDispatch* pParam = varParam.pdispVal;

    // 3. Устанавливаем значение через ValueAsString
    OLECHAR* propValueAsString = L"ValueAsString";
    hr = pParam->GetIDsOfNames(IID_NULL, &propValueAsString, 1,
        LOCALE_USER_DEFAULT, &dispid);
    if (FAILED(hr)) {
        pParam->Release();
        VariantClear(&varParam);
        return false;
    }

    // Подготавливаем значение
    VARIANT varValue;
    VariantInit(&varValue);
    varValue.vt = VT_BSTR;
    varValue.bstrVal = SysAllocString(value);

    // Для PROPERTYPUT нужен именованный аргумент DISPID_PROPERTYPUT
    DISPID dispidNamed = DISPID_PROPERTYPUT;
    DISPPARAMS valueParams;
    valueParams.rgvarg = &varValue;
    valueParams.cArgs = 1;
    valueParams.rgdispidNamedArgs = &dispidNamed;  // ВАЖНО!
    valueParams.cNamedArgs = 1;                     // ВАЖНО!

    VARIANT varSetResult;
    VariantInit(&varSetResult);

    hr = pParam->Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT,
        DISPATCH_PROPERTYPUT, &valueParams,
        &varSetResult, NULL, NULL);

    // Очистка
    pParam->Release();
    VariantClear(&varParam);
    VariantClear(&varValue);
    VariantClear(&varSetResult);

    return SUCCEEDED(hr);
}

bool AWRInterface::SaveProject(const std::wstring& filePath) {
    if (!m_pProject) return false;

    DISPPARAMS params;
    VARIANT args[1];
    args[0].vt = VT_BSTR;
    args[0].bstrVal = SysAllocString(filePath.c_str());

    params.rgvarg = args;
    params.cArgs = 1;
    params.rgdispidNamedArgs = nullptr;
    params.cNamedArgs = 0;

    VARIANT result;
    VariantInit(&result);

    HRESULT hr = InvokeMethod(m_pProject, L"SaveAs", &result, DISPATCH_METHOD, &params);

    SysFreeString(args[0].bstrVal);

    return SUCCEEDED(hr);
}

HRESULT AWRInterface::InvokeMethod(IDispatch* pDisp, LPCOLESTR methodName,
    VARIANT* pResult, WORD wFlags,
    DISPPARAMS* pParams) 
{
    DISPID dispid;
    HRESULT hr = pDisp->GetIDsOfNames(IID_NULL, const_cast<LPOLESTR*>(&methodName),
        1, LOCALE_USER_DEFAULT, &dispid);
    if (FAILED(hr)) return hr;

    DISPPARAMS noParams = { nullptr, nullptr, 0, 0 };
    if (!pParams) pParams = &noParams;

    return pDisp->Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT,
        wFlags, pParams, pResult, nullptr, nullptr);
}

HRESULT AWRInterface::GetProperty(IDispatch* pDisp, LPCOLESTR propName, VARIANT* pResult) 
{
    return InvokeMethod(pDisp, propName, pResult, DISPATCH_PROPERTYGET);
}

HRESULT AWRInterface::SetProperty(IDispatch* pDisp, LPCOLESTR propName, VARIANT* pValue)
{
    DISPID dispid;
    HRESULT hr = pDisp->GetIDsOfNames(IID_NULL, const_cast<LPOLESTR*>(&propName),
        1, LOCALE_USER_DEFAULT, &dispid);
    if (FAILED(hr)) return hr;

    DISPID putID = DISPID_PROPERTYPUT;
    DISPPARAMS params;
    params.rgvarg = pValue;
    params.cArgs = 1;
    params.rgdispidNamedArgs = &putID;
    params.cNamedArgs = 1;

    return pDisp->Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT,
        DISPATCH_PROPERTYPUT, &params, nullptr, nullptr, nullptr);
}*/