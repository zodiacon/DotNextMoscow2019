// View.h : interface of the CView class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include "VirtualListView.h"

class CView : 
	public CWindowImpl<CView, CListViewCtrl>,
	public CVirtualListView<CView> {
public:
	DECLARE_WND_SUPERCLASS(nullptr, CListViewCtrl::GetWndClassName())

	BOOL PreTranslateMessage(MSG* pMsg);
	void DoSort(const SortInfo*);
	bool IsFileOpen() const;
	void Close();
	void Reload();

	BEGIN_MSG_MAP(CView)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		REFLECTED_NOTIFY_CODE_HANDLER(LVN_GETDISPINFO, OnGetDispInfo)
		MESSAGE_HANDLER(CFindReplaceDialog::GetFindReplaceMsg(), OnDoFind)
		CHAIN_MSG_MAP_ALT(CVirtualListView<CView>, 1)
	ALT_MSG_MAP(1)
		COMMAND_ID_HANDLER(ID_FILE_OPEN, OnFileOpen)
		COMMAND_ID_HANDLER(ID_EDIT_FIND, OnEditFind)
		COMMAND_ID_HANDLER(ID_FILE_CLOSE, OnFileClose)
	END_MSG_MAP()

	// Handler prototypes (uncomment arguments if needed):
	//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

private:
	bool LoadFile(PCWSTR);

private:
	LRESULT OnGetDispInfo(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/);
	LRESULT OnFileOpen(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnEditFind(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnFileClose(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnDoFind(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

	enum class LogLevel {
		Mandatory = 0,
		Critical,
		Error,
		Warning,
		Info,
		Debug,
		Trace
	};

	struct LineInfo {
		SYSTEMTIME DateTime;
		int64_t DateTime64;
		int Microsec;
		LogLevel Level;
		unsigned Pid, Tid;
		CString Module;
		CString Message;
	};

	static LogLevel ParseLogLevel(const CString& slevel);
	static PCWSTR LogLevelToString(LogLevel level);
	static CString GetNextToken(const CString& str, PCWSTR delim, int& start);
	static bool CompareItems(const LineInfo& l1, const LineInfo& l2, const SortInfo* si);

	std::vector<LineInfo> m_Lines;
	CString m_FileName;
	CImageListManaged m_Images;
	CFindReplaceDialog* m_pFindDlg{ nullptr };
};
