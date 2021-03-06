
// MFCTreeCtrlDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MFCTreeCtrl.h"
#include "MFCTreeCtrlDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCTreeCtrlDlg 对话框



CMFCTreeCtrlDlg::CMFCTreeCtrlDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCTREECTRL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCTreeCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_tree);
}

BEGIN_MESSAGE_MAP(CMFCTreeCtrlDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCTreeCtrlDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCTreeCtrlDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCTreeCtrlDlg::OnBnClickedButton1)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE1, &CMFCTreeCtrlDlg::OnNMDblclkTree1)
END_MESSAGE_MAP()


// CMFCTreeCtrlDlg 消息处理程序

BOOL CMFCTreeCtrlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_tree.ModifyStyle(NULL, TVS_HASBUTTONS | TVS_LINESATROOT | TVS_HASLINES);

	((CEdit*)GetDlgItem(IDC_EDIT1))->SetLimitText(10 * 1024 * 1024 * 1024);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCTreeCtrlDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCTreeCtrlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCTreeCtrlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCTreeCtrlDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void CMFCTreeCtrlDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}

LPWSTR asc_to_wide(const char* str)
{
	LPWSTR wstr;
	int len_0, sz;
	if (!str)
		return NULL;
	len_0 = strlen(str) + 1;
	sz = MultiByteToWideChar(CP_ACP, 0, str, len_0, NULL, 0);
	if (!sz) {
		return NULL;
	}
	wstr = (LPWSTR)malloc(sz * sizeof(wchar_t));
	if (!wstr) {
		return NULL;
	}
	if (!MultiByteToWideChar(CP_ACP, 0, str, len_0, wstr, sz)) {
		free(wstr);
		return NULL;
	}
	return wstr;
}


char *wide_to_asc(LPCWSTR wstr)
{
	char *str;
	int len_0, sz;

	if (!wstr)
		return NULL;
	len_0 = (int)wcslen(wstr) + 1; /* WideCharToMultiByte expects int */
	sz = WideCharToMultiByte(CP_ACP, 0, wstr, len_0, NULL, 0, NULL, NULL);
	if (!sz) {
		return NULL;
	}
	str = (char *)malloc(sz);
	if (!str) {
		return NULL;
	}
	if (!WideCharToMultiByte(CP_ACP, 0, wstr, len_0, str, sz, NULL, NULL)) {
		free(str);
		return NULL;
	}
	return str;
}




std::string _w2a(const wchar_t *w)
{
	std::string str;
	char *astr = wide_to_asc(w);
	if (astr) {
		str = astr;
		free(astr);
	}
	return str;
}

std::wstring _a2w(const char *a)
{
	std::wstring wstr;
	wchar_t *w = asc_to_wide(a);
	if (w) {
		wstr = w;
		free(w);
	}
	return wstr;
}

void HexToStr(unsigned char *pbDest, unsigned char *pbSrc, int nLen)
{
	char    ddl, ddh;
	int i;

	for (i = 0; i < nLen; i++)
	{
		ddh = 48 + pbSrc[i] / 16;
		ddl = 48 + pbSrc[i] % 16;
		if (ddh > 57) ddh = ddh + 7;
		if (ddl > 57) ddl = ddl + 7;
		pbDest[i * 3] = ddh;
		pbDest[i * 3 + 1] = ddl;
		pbDest[i * 3 + 2] = ' ';
	}

	pbDest[nLen * 3] = '\0';
}

void StrToHex(char *pbDest, char *pbSrc, int nLen)
{
	char h1, h2;
	char s1, s2;
	int i;

	for (i = 0; i < nLen; i++)
	{
		h1 = pbSrc[2 * i];
		h2 = pbSrc[2 * i + 1];

		s1 = toupper(h1) - 0x30;
		if (s1 > 9)
			s1 -= 7;

		s2 = toupper(h2) - 0x30;
		if (s2 > 9)
			s2 -= 7;

		pbDest[i] = s1 * 16 + s2;
	}
}

std::string UTF8ToGB(const char* str)
{
	string result;
	WCHAR* strSrc;
	CHAR* szRes;

	//获得临时变量的大小
	int i = MultiByteToWideChar(CP_UTF8, 0, str, -1, nullptr, 0);
	strSrc = new WCHAR[i + 1];
	MultiByteToWideChar(CP_UTF8, 0, str, -1, strSrc, i);

	//获得临时变量的大小
	i = WideCharToMultiByte(CP_ACP, 0, strSrc, -1, nullptr, 0, nullptr, nullptr);
	szRes = new CHAR[i + 1];
	WideCharToMultiByte(CP_ACP, 0, strSrc, -1, szRes, i, nullptr, nullptr);

	result = szRes;
	delete[]strSrc;
	delete[]szRes;

	return result;
}

string GBToUTF8(const char* str)
{
	string result;
	WCHAR* strSrc;
	CHAR* szRes;

	//获得临时变量的大小
	int i = MultiByteToWideChar(CP_ACP, 0, str, -1, nullptr, 0);
	strSrc = new WCHAR[i + 1];
	MultiByteToWideChar(CP_ACP, 0, str, -1, strSrc, i);

	//获得临时变量的大小
	i = WideCharToMultiByte(CP_UTF8, 0, strSrc, -1, nullptr, 0, nullptr, nullptr);
	szRes = new CHAR[i + 1];
	memset(szRes, 0, i + 1);
	int j = WideCharToMultiByte(CP_UTF8, 0, strSrc, -1, szRes, i, nullptr, nullptr);

	result = szRes;
	delete[]strSrc;
	delete[]szRes;

	return result;
}

int IsTextUTF8(char* str, ULONGLONG length)
{
	int i;
	DWORD nBytes = 0;//UFT8可用1-6个字节编码,ASCII用一个字节
	UCHAR chr;
	BOOL bAllAscii = TRUE; //如果全部都是ASCII, 说明不是UTF-8
	for (i = 0; i < length; i++)
	{
		chr = *(str + i);
		if ((chr & 0x80) != 0) // 判断是否ASCII编码,如果不是,说明有可能是UTF-8,ASCII用7位编码,但用一个字节存,最高位标记为0,o0xxxxxxx
			bAllAscii = FALSE;
		if (nBytes == 0) //如果不是ASCII码,应该是多字节符,计算字节数
		{
			if (chr >= 0x80)
			{
				if (chr >= 0xFC && chr <= 0xFD)
					nBytes = 6;
				else if (chr >= 0xF8)
					nBytes = 5;
				else if (chr >= 0xF0)
					nBytes = 4;
				else if (chr >= 0xE0)
					nBytes = 3;
				else if (chr >= 0xC0)
					nBytes = 2;
				else
				{
					return FALSE;
				}
				nBytes--;
			}
		}
		else //多字节符的非首字节,应为 10xxxxxx
		{
			if ((chr & 0xC0) != 0x80)
			{
				return FALSE;
			}
			nBytes--;
		}
	}
	if (nBytes > 0) //违返规则
	{
		return FALSE;
	}
	if (bAllAscii) //如果全部都是ASCII, 说明不是UTF-8
	{
		return FALSE;
	}
	return TRUE;
}


void CMFCTreeCtrlDlg::PrintUnknownFields(
	const UnknownFieldSet& unknown_fields, HTREEITEM parent) {
	for (int i = 0; i < unknown_fields.field_count(); i++) {
		const UnknownField& field = unknown_fields.field(i);
		string field_number = SimpleItoa(field.number());

		switch (field.type()) {
		case UnknownField::TYPE_VARINT: {
			HTREEITEM hCurItem = m_tree.InsertItem(_a2w(std::string("(" + field_number + ")" + "Varint").c_str()).c_str(), parent);
			m_tree.SetItemData(hCurItem, DECSCRIPTION);
			hCurItem = m_tree.InsertItem(_a2w(SimpleItoa(field.varint()).c_str()).c_str(), hCurItem);
			m_tree.SetItemData(hCurItem, OTHER_DATA);
			break;
		}
		case UnknownField::TYPE_FIXED32: {
			HTREEITEM hCurItem = m_tree.InsertItem(_a2w(std::string("(" + field_number + ")" + "Fixed32").c_str()).c_str(), parent);
			m_tree.SetItemData(hCurItem, DECSCRIPTION);
			
			hCurItem = m_tree.InsertItem(_a2w(SimpleItoa(field.fixed32()).c_str()).c_str(), hCurItem);
			m_tree.SetItemData(hCurItem, OTHER_DATA);
			break;
		}
		case UnknownField::TYPE_FIXED64: {
			HTREEITEM hCurItem = m_tree.InsertItem(_a2w(std::string("(" + field_number + ")" + "Fixed64").c_str()).c_str(), parent);
			m_tree.SetItemData(hCurItem, DECSCRIPTION);
			
			hCurItem = m_tree.InsertItem(_a2w(SimpleItoa(field.fixed64()).c_str()).c_str(), hCurItem);
			m_tree.SetItemData(hCurItem, OTHER_DATA);
			break;
		}
		case UnknownField::TYPE_LENGTH_DELIMITED: {
			const string& value = field.length_delimited();
			UnknownFieldSet embedded_unknown_fields;

			HTREEITEM hCurItem = m_tree.InsertItem(_a2w(std::string("(" + field_number + ")" + "Length_Delimited" + "(length: " + std::to_string(value.length()) + ")").c_str()).c_str(), parent);
			m_tree.SetItemData(hCurItem, DECSCRIPTION);
			if (!value.empty() && embedded_unknown_fields.ParseFromString(value)) {

				PrintUnknownFields(embedded_unknown_fields, hCurItem);

			}
			else {
				// This field is not parseable as a Message.
				// So it is probably just a plain string.

				int len = value.length() * 3 + 1;
				std::shared_ptr<char> hexstr = std::shared_ptr<char>(new char[len], [](char *p) { delete[]p; });
				memset(hexstr.get(), 0, len);

				HexToStr((unsigned char *)hexstr.get(), (unsigned char *)value.c_str(), value.length());

				std::string &temp = std::string((const char *)hexstr.get());


				hCurItem = m_tree.InsertItem(_a2w( (temp + "(" + value + ")").c_str() ).c_str(), hCurItem);
				m_tree.SetItemData(hCurItem, DELIMITED_DATA);
			}
			break;
		}
		case UnknownField::TYPE_GROUP: {
			HTREEITEM hCurItem = m_tree.InsertItem(_a2w(std::string("(" + field_number + ")" + "group").c_str()).c_str(), parent);
			const UnknownFieldSet &embedded_unknown_fields = field.group();
			PrintUnknownFields(embedded_unknown_fields, hCurItem);

			break;
		}
		}
	}
}

void ExpandAllNode(HTREEITEM hItem, CTreeCtrl& m_treeShow) {

	HTREEITEM hChild = m_treeShow.GetChildItem(hItem); //获得第一个子节点

	while (hChild) {

		m_treeShow.Expand(hItem, TVE_EXPAND); //展开当前节点

		ExpandAllNode(hChild, m_treeShow); //递归展开第一个子节点下所有节点

		hChild = m_treeShow.GetNextSiblingItem(hChild); //获得第二个子节点

	}

}

/******************************************************************************
字符串替换
******************************************************************************/
void __ReplaceString(string & strReplace, string strOld, string strNew)
{
	string::size_type nFindStartPos = 0;
	string::size_type nFoundPos = string::npos;
	string::size_type nOldLen = strOld.length();
	string::size_type nNewLen = strNew.length();

	//要替换的字符串为空，没法替换
	if (strOld == ""
		|| nOldLen == 0)
	{
		return;
	}

	//源串为空，没法替换
	if (strReplace == "")
	{
		return;
	}

	//替换每一处
	while (true)
	{
		//寻找要替换的字符串位置
		nFoundPos = strReplace.find(strOld, nFindStartPos);

		if (nFoundPos == string::npos)
		{
			break;
		}

		//替换掉
		strReplace.replace(nFoundPos, nOldLen, strNew);

		//搜索起始位置下移
		nFindStartPos = nFoundPos + nNewLen;

		if (nFindStartPos >= strReplace.length())
		{
			break;
		}
	}
}

void CMFCTreeCtrlDlg::OnBnClickedButton1()
{
	CString str;
	GetDlgItemText(IDC_EDIT1, str);
	SetTemp_data(_w2a(str.GetBuffer()));

	__ReplaceString(GetTemp_data(), " ", "");
	__ReplaceString(GetTemp_data(), "(", "");
	__ReplaceString(GetTemp_data(), ")", "");
	__ReplaceString(GetTemp_data(), "\r", "");
	__ReplaceString(GetTemp_data(), "\n", "");

	int len = GetTemp_data().length() / 2;
	std::shared_ptr<char> dest = std::shared_ptr<char>(new char[len], [](char *p) {delete p; });
	memset(dest.get(), 0, len);
	StrToHex(dest.get(), (char *)GetTemp_data().c_str(), len);
	m_tree.DeleteAllItems();
	HTREEITEM root = m_tree.InsertItem(_T("ROOT"));
	UnknownFieldSet unknown_fields;
	if (unknown_fields.ParseFromString(std::string((const char *)dest.get(), len))) {

		PrintUnknownFields(unknown_fields, root);
	}

	
// 	std::string filename = ".\\2.bin";
// 	std::ifstream infile(filename, std::ios::binary);
// 	if (infile.is_open()) {
// 		infile.seekg(0, ios_base::end);
// 		int len = infile.tellg();
// 		char *buffer = new char[len];
// 		infile.seekg(0, ios_base::beg);
// 		infile.read(buffer, len);
// 		infile.close();
// 
// 		UnknownFieldSet unknown_fields;
// 		if (unknown_fields.ParseFromString(std::string((const char *)buffer, len))) {
// 			
// 			PrintUnknownFields(unknown_fields, root);
// 		}
// 	}
	ExpandAllNode(root, m_tree);
}


void CMFCTreeCtrlDlg::OnNMDblclkTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	parserdlg.SetData(temp_data);
	parserdlg.DoModal();

	*pResult = 0;
}
