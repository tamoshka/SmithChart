/*#pragma once

#include <windows.h>
#include "circuitElements.h"
#include <comdef.h>
#include <atlbase.h>
#include <string>
#include <vector>
#include <stdexcept>

class AWRInterface {
public:
    AWRInterface(CircuitElements* circuit);
    ~AWRInterface();

    bool Initialize();
    void Cleanup();

    bool CreateProject(const std::wstring& projectName);
    bool ClearAllElements();
    bool ClearAllPortElements(bool);
    bool ClearAllWires();
    bool SetFrequencySweep(double startFreq, double stopFreq, int numPoints);
    bool SetSingleFrequency(double frequency);
    bool SetSweepType(bool isLinear);
    bool AddSchematic(const std::wstring& schematicName);
    bool AddPortSchematic(const std::wstring& schematicName, bool);
    bool AddPortElement(const std::wstring& elementType, double x, double y, double angle, bool);
    bool AddElement(const std::wstring& elementType, double x, double y, double angle);
    bool AddWire(double x1, double y1, double x2, double y2);
    bool SetElementParameter(const wchar_t* paramName, const wchar_t* value);
    bool SetStringElementParameter(const wchar_t* paramName, const wchar_t* value);
    bool SaveProject(const std::wstring& filePath);
    IDispatch* m_pAWRApp;
    IDispatch* m_pProject;
    IDispatch* m_pSchematic;
    IDispatch* m_portSchematic;
    IDispatch* m_port2Schematic;
    IDispatch* m_pLastElement;

private:
    CircuitElements* circuitElements;
    bool ParseValueAndUnits(const wchar_t* str, double& value, std::wstring& units);
    double ConvertToSI(double value, const wchar_t* unit);

    bool m_bInitialized;

    // Вспомогательные функции для работы с COM
    HRESULT InvokeMethod(IDispatch* pDisp, LPCOLESTR methodName,
        VARIANT* pResult, WORD wFlags,
        DISPPARAMS* pParams = nullptr);

    HRESULT GetProperty(IDispatch* pDisp, LPCOLESTR propName, VARIANT* pResult);
    HRESULT SetProperty(IDispatch* pDisp, LPCOLESTR propName, VARIANT* pValue);
};
*/