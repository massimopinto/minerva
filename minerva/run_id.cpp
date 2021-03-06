// run_id.h : Implementation of the Crun_id class



// Crun_id implementation

// code generated on gioved� 24 maggio 2018, 14:33

#include "stdafx.h"
#include "run_id.h"
IMPLEMENT_DYNAMIC(Crun_id, CRecordset)

Crun_id::Crun_id(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_date = "";
	m_hour;
	m_t_mon_begin = 0.0;
	m_t_mon_end = 0.0;
	m_t_core_begin = 0.0;
	m_t_core_end = 0.0;
	m_calibration_mode = FALSE;
	m_T = 0.0;
	m_P = 0.0;
	m_H = 0.0;
	m_RX_Qual = "";
	m_Delta_VMON = 0.0;
	m_katt = 0.0;
	m_ktp = 0.0;
	m_QMON = 0.0;
	m_injected_power = 0.0;
	m_Injected_energy = 0.0;
	m_Capacitance = 0.0;
	m_delta_R = 0.0;
	m_mid_R = 0.0;
	m_deltaR_over_R = 0.0;
	m_preDrift_intercept = 0.0;
	m_preDrift_slope = 0.0;
	m_postDrift_intercept = 0.0;
	m_postDrift_slope = 0.0;
	m_nFields = 26;
	m_nDefaultType = snapshot;
}
// #error Security Issue: The connection string may contain a password
// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString Crun_id::GetDefaultConnect()
{
	return _T("DSN=192.168.120.102;SERVER=192.168.120.102;UID=misuraUser;PWD=musy1981;DATABASE=calorimetroRX;PORT=3306");
}

CString Crun_id::GetDefaultSQL()
{
	return _T("[run_id]");
}

void Crun_id::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[date]"), m_date);
	RFX_Date(pFX, _T("[hour]"), m_hour);
	RFX_Double(pFX, _T("[t_mon_begin]"), m_t_mon_begin);
	RFX_Double(pFX, _T("[t_mon_end]"), m_t_mon_end);
	RFX_Double(pFX, _T("[t_core_begin]"), m_t_core_begin);
	RFX_Double(pFX, _T("[t_core_end]"), m_t_core_end);
	RFX_Bool(pFX, _T("[calibration_mode]"), m_calibration_mode);
	RFX_Double(pFX, _T("[T]"), m_T);
	RFX_Double(pFX, _T("[P]"), m_P);
	RFX_Double(pFX, _T("[H]"), m_H);
	RFX_Text(pFX, _T("[RX_Qual]"), m_RX_Qual);
	RFX_Double(pFX, _T("[Delta_VMON]"), m_Delta_VMON);
	RFX_Double(pFX, _T("[katt]"), m_katt);
	RFX_Double(pFX, _T("[ktp]"), m_ktp);
	RFX_Double(pFX, _T("[QMON]"), m_QMON);
	RFX_Double(pFX, _T("[injected_power]"), m_injected_power);
	RFX_Double(pFX, _T("[Injected_energy]"), m_Injected_energy);
	RFX_Double(pFX, _T("[Capacitance]"), m_Capacitance);
	RFX_Double(pFX, _T("[delta_R]"), m_delta_R);
	RFX_Double(pFX, _T("[mid_R]"), m_mid_R);
	RFX_Double(pFX, _T("[deltaR_over_R]"), m_deltaR_over_R);
	RFX_Double(pFX, _T("[preDrift_intercept]"), m_preDrift_intercept);
	RFX_Double(pFX, _T("[preDrift_slope]"), m_preDrift_slope);
	RFX_Double(pFX, _T("[postDrift_intercept]"), m_postDrift_intercept);
	RFX_Double(pFX, _T("[postDrift_slope]"), m_postDrift_slope);

}
/////////////////////////////////////////////////////////////////////////////
// Crun_id diagnostics

#ifdef _DEBUG
void Crun_id::AssertValid() const
{
	CRecordset::AssertValid();
}

void Crun_id::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


