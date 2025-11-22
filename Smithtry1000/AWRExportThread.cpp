#include "AWRExportThread.h"

AWRExportThread::AWRExportThread(Smithtry1000* parent) :
	m_parent(parent),
	m_success(false) 
{

}

bool AWRExportThread::getSuccess() const 
{
	return m_success;
}

void AWRExportThread::run()
{
	m_success = m_parent->ExportToAWR();
}