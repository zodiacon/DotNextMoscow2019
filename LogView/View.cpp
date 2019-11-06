// View.cpp : implementation of the CView class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include <fstream>
#include "View.h"
#include <atltime.h>
#include <algorithm>

BOOL CView::PreTranslateMessage(MSG* pMsg) {
	if (m_pFindDlg && m_pFindDlg->IsDialogMessageW(pMsg))
		return TRUE;

	return FALSE;
}

void CView::DoSort(const SortInfo* si) {
	std::sort(m_Lines.begin(), m_Lines.end(), [si](const auto& l1, const auto& l2) {
		return CompareItems(l1, l2, si);
		});

	RedrawItems(GetTopIndex(), GetTopIndex() + GetCountPerPage());
}

bool CView::IsFileOpen() const {
	return !m_Lines.empty();
}

void CView::Close() {
	m_Lines.clear();
	SetItemCount(0);
}

void CView::Reload() {
	Close();
	if (!LoadFile(m_FileName)) {
		AtlMessageBox(*this, L"Failed to reload file", IDR_MAINFRAME);
	}
	SetItemCount(static_cast<int>(m_Lines.size()));
}

bool CView::LoadFile(PCWSTR path) {
	std::ifstream stm;
	stm.open(path);
	if (!stm.is_open())
		return false;

	char text[4096];

	std::vector<LineInfo> lines;
	lines.reserve(64);

	while (!stm.eof()) {
		stm.getline(text, sizeof(text));
		// parse line
		LineInfo line;
		CString stext(text);
		if (stext.IsEmpty())
			break;

		int start = 0;
		auto token = GetNextToken(stext, L"[\t ]", start);
		if (token.IsEmpty())
			return false;

		// should be date
		token.Trim();
		SYSTEMTIME st = { 0 };
		st.wMonth = ::_wtoi(token.Left(2));
		st.wDay = ::_wtoi(token.Mid(3, 2));
		bool is4yeardigits = token.GetLength() > 8;
		st.wYear = ::_wtoi(token.Mid(6, is4yeardigits ? 4 : 2));
		if (!is4yeardigits)
			st.wYear += 2000;

		// time

		token = GetNextToken(stext, L"]", start);
		if (token.IsEmpty())
			return false;

		st.wHour = ::_wtoi(token.Left(2));
		st.wMinute = ::_wtoi(token.Mid(3, 2));
		st.wSecond = ::_wtoi(token.Mid(6, 2));

		line.DateTime = st;
		::SystemTimeToFileTime(&st, (FILETIME*)& line.DateTime64);

		// log level

		token = GetNextToken(stext, L"[]", start);
		line.Level = ParseLogLevel(token);

		// PID, TID

		token = GetNextToken(stext, L"[,", start);

		line.Pid = ::_wtoi(token);
		token = stext.Tokenize(L"]", start);
		line.Tid = ::_wtoi(token);

		// finally, the message 
		line.Message = stext.Mid(start).Trim();

		lines.emplace_back(line);
	}

	m_Lines = std::move(lines);

	return true;
}

LRESULT CView::OnGetDispInfo(int, LPNMHDR hdr, BOOL&) {
	auto lv = (NMLVDISPINFO*)hdr;
	auto& item = lv->item;
	auto& data = m_Lines[item.iItem];

	if (item.mask & LVIF_TEXT) {
		switch (item.iSubItem) {
			case 0:		// date/time
				::StringCchCopy(item.pszText, item.cchTextMax, CTime(data.DateTime).Format(L"%D %X"));
				break;

			case 1:		// level
				::StringCchCopy(item.pszText, item.cchTextMax, LogLevelToString(data.Level));
				break;

			case 2:		// PID
				::StringCchPrintf(item.pszText, item.cchTextMax, L"%d (0x%X)", data.Pid, data.Pid);
				break;

			case 3:		// TID
				::StringCchPrintf(item.pszText, item.cchTextMax, L"0x%X", data.Tid);
				break;

			case 4:		// message
				item.pszText = (PWSTR)(PCWSTR)data.Message;
				break;
		}
	}
	if (item.mask & LVIF_IMAGE) {
		item.iImage = static_cast<int>(data.Level);
	}

	return 0;
}

LRESULT CView::OnFileOpen(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/) {
	CSimpleFileDialog dlg(TRUE, L".log");
	if (dlg.DoModal() == IDOK) {
		if (!LoadFile(dlg.m_szFileName)) {
			MessageBox(L"Failed to load log file", L"Log Viewer");
		}
		m_FileName = dlg.m_szFileName;
		WCHAR title[128];
		AtlLoadString(IDR_MAINFRAME, title, 128);
		GetParent().SetWindowTextW(CString(title) + L" (" + m_FileName + L")");

		SetItemCount(static_cast<int>(m_Lines.size()));
	}
	return 0;
}

LRESULT CView::OnEditFind(WORD, WORD, HWND, BOOL&) {
	if (m_pFindDlg == nullptr) {
		m_pFindDlg = new CFindReplaceDialog();
		m_pFindDlg->Create(TRUE, nullptr, nullptr, FR_DOWN | FR_HIDEWHOLEWORD, *this);
	}
	m_pFindDlg->ShowWindow(SW_SHOW);

	return 0;
}

LRESULT CView::OnFileClose(WORD, WORD, HWND, BOOL&) {
	m_Lines.clear();
	WCHAR title[128];
	AtlLoadString(IDR_MAINFRAME, title, 128);
	GetParent().SetWindowTextW(title);
	SetItemCount(0);

	return 0;
}

LRESULT CView::OnCreate(UINT, WPARAM, LPARAM, BOOL&) {
	DefWindowProc();

	struct {
		PCWSTR Header;
		int Width;
		int Format = LVCFMT_LEFT;
	} columns[] = {
		{ L"Date / Time", 120 },
		{ L"Level", 100 },
		{ L"Process ID", 100, LVCFMT_RIGHT },
		{ L"Thread ID", 100, LVCFMT_RIGHT },
		{ L"Message", 500 }
	};

	int i = 0;
	for (auto& c : columns)
		InsertColumn(i++, c.Header, c.Format, c.Width);

	SetExtendedListViewStyle(LVS_EX_DOUBLEBUFFER | LVS_EX_FULLROWSELECT);

	m_Images.Create(16, 16, ILC_COLOR32 | ILC_COLOR, 8, 4);

	UINT ids[] = {
		IDI_MANDATORY, IDI_FATAL, IDI_ERROR2, IDI_WARNING2,
		IDI_INFO, IDI_DEBUG, IDI_TRACE
	};
	for (auto id : ids)
		m_Images.AddIcon(AtlLoadIcon(id));

	SetImageList(m_Images, LVSIL_SMALL);

	return 0;
}

LRESULT CView::OnDoFind(UINT, WPARAM, LPARAM, BOOL&) {
	if (m_pFindDlg == nullptr)
		return 0;

	if (m_pFindDlg->IsTerminating()) {
		m_pFindDlg = nullptr;
		return 0;
	}

	auto caseSensitive = m_pFindDlg->MatchCase();
	auto down = m_pFindDlg->SearchDown();
	CString text(m_pFindDlg->GetFindString());
	if (!caseSensitive)
		text.MakeLower();

	int start = GetSelectionMark();
	int count = GetItemCount();
	int from = start + 1, limit = start + count, step = 1;
	if (!down) {
		from = start - 1;
		step = -1;
		limit = start - count;
	}
	for (int i = from; down ? (i < limit) : (i > limit) ; i += step) {
		for (int c = 0; c < 6; c++) {
			int index = (count * 2 + i) % count;
			CString data;
			GetItemText(index, c, data);
			if (!caseSensitive)
				data.MakeLower();
			if (data.Find(text) >= 0) {
				SetItemState(-1, 0, LVIS_SELECTED | LVIS_FOCUSED);
				SetItemState(index, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
				SetSelectionMark(index);
				EnsureVisible(index, FALSE);
				return 0;
			}
		}
	}

	m_pFindDlg->EnableWindow(FALSE);
	MessageBox(L"Not found", L"Sealights Log Viewer", MB_TASKMODAL);
	m_pFindDlg->EnableWindow(TRUE);
	return 0;
}

CView::LogLevel CView::ParseLogLevel(const CString& slevel) {
	CString level(slevel);
	level.MakeLower();

	static const struct {
		LogLevel Level;
		PCWSTR Name;
	} levels[] = {
		{ LogLevel::Trace, L"trace" },
		{ LogLevel::Debug, L"debug" },
		{ LogLevel::Info, L"info" },
		{ LogLevel::Mandatory, L"mandatory" },
		{ LogLevel::Warning, L"warning" },
		{ LogLevel::Error, L"error" },
		{ LogLevel::Critical, L"critical" },
	};

	for (auto& l : levels)
		if (level == l.Name)
			return l.Level;

	return LogLevel::Mandatory;
}

PCWSTR CView::LogLevelToString(LogLevel level) {
	switch (level) {
		case LogLevel::Mandatory: return L"MANDATORY";
		case LogLevel::Debug: return L"DEBUG";
		case LogLevel::Info: return L"INFO";
		case LogLevel::Warning: return L"WARNING";
		case LogLevel::Error: return L"ERROR";
		case LogLevel::Critical: return L"CRITICAL";
		case LogLevel::Trace: return L"TRACE";
	}
	return L"";
}

CString CView::GetNextToken(const CString& str, PCWSTR delim, int& start) {
	auto token = str.Tokenize(delim, start);
	if (token.Trim().IsEmpty())
		token = str.Tokenize(delim, start);
	return token.Trim();
}

bool CView::CompareItems(const LineInfo& l1, const LineInfo& l2, const SortInfo* si) {
	switch (si->SortColumn) {
		case 0:		// date/time
			return SortNumbers(l1.DateTime64, l2.DateTime64, si->SortAscending);

		case 1:		// level
			return SortStrings(LogLevelToString(l1.Level), LogLevelToString(l2.Level), si->SortAscending);

		case 2:		// PID
			return SortNumbers(l1.Pid, l2.Pid, si->SortAscending);

		case 3:		// TID
			return SortNumbers(l1.Tid, l2.Tid, si->SortAscending);

		case 4:		// message
			return SortStrings(l1.Message, l2.Message, si->SortAscending);
	}
	ATLASSERT(false);
	return false;
}
