// run_id.h : Declaration of the Crun_id

#pragma once

// code generated on giovedì 24 maggio 2018, 14:33

class Crun_id : public CRecordset
{
public:
	Crun_id(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(Crun_id)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

	long	m_ID;
	CStringA	m_date;
	CTime	m_hour;
	double	m_t_mon_begin;
	double	m_t_mon_end;
	double	m_t_core_begin;
	double	m_t_core_end;
	BOOL	m_calibration_mode;
	double	m_T;
	double	m_P;
	double	m_H;
	CStringA	m_RX_Qual;
	double	m_Delta_VMON;
	double	m_katt;
	double	m_ktp;
	double	m_QMON;
	double	m_injected_power;
	double	m_Injected_energy;
	double	m_Capacitance;
	double	m_delta_R;
	double	m_mid_R;
	double	m_deltaR_over_R;
	double	m_preDrift_intercept;
	double	m_preDrift_slope;
	double	m_postDrift_intercept;
	double	m_postDrift_slope;

// Overrides
	// Wizard generated virtual function overrides
	public:
	virtual CString GetDefaultConnect();	// Default connection string

	virtual CString GetDefaultSQL(); 	// default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX support

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


