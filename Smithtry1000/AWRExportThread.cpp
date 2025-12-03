#include "AWRExportThread.h"

/// <summary>
/// Конструктор класса.
/// </summary>
/// <param name="parent">Родительский виджет.</param>
AWRExportThread::AWRExportThread(Smithtry1000* parent) :
	m_parent(parent),
	m_success(false) 
{

}

/// <summary>
/// Успех экспорта в AWR.
/// </summary>
/// <returns></returns>
bool AWRExportThread::getSuccess() const 
{
	return m_success;
}

/// <summary>
/// Запуск экспорта в AWR.
/// </summary>
void AWRExportThread::run()
{
	m_success = m_parent->ExportToAWR();
}