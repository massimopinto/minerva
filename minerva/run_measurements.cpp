// run_measurements.h : Implementation of the Crun_measurements class



// Crun_measurements implementation

// code generated on venerdì 11 maggio 2018, 11:16

#include "stdafx.h"
#include "run_measurements.h"
IMPLEMENT_DYNAMIC(Crun_measurements, CRecordset)

Crun_measurements::Crun_measurements(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_ID_RUN = 0;
	m_time = 0.0;
	m_resistance = 0.0;
	m_nFields = 4;
	m_nDefaultType = snapshot;
}
//#error Security Issue: The connection string may contain a password
// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString Crun_measurements::GetDefaultConnect()
{
	return _T("ODBC;DSN=192.168.120.102;SERVER=192.168.120.102;UID=misuraUser;PWD=musy1981;DATABASE=calorimetroRX;PORT=3306");
}

CString Crun_measurements::GetDefaultSQL()
{
	return _T("[run_measurements]");
}

void Crun_measurements::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Long(pFX, _T("[ID_RUN]"), m_ID_RUN);
	RFX_Double(pFX, _T("[time]"), m_time);
	RFX_Double(pFX, _T("[resistance]"), m_resistance);

}
/////////////////////////////////////////////////////////////////////////////
// Crun_measurements diagnostics

#ifdef _DEBUG
void Crun_measurements::AssertValid() const
{
	CRecordset::AssertValid();
}

void Crun_measurements::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


