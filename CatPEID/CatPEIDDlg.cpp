
// CatPEIDDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CatPEID.h"
#include "CatPEIDDlg.h"
#include "afxdialogex.h"
#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CString unixTime2Str(DWORD n);
CString ExpandShortcut(CString &inFile);
CList<IMAGE_SECTION_HEADER, IMAGE_SECTION_HEADER>m_images;//ȫ�ֵ�IMAGE_SECTION_HEARDS ���� RAV->RAW
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CCatPEIDDlg �Ի���



CCatPEIDDlg::CCatPEIDDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CATPEID_DIALOG, pParent)
	, m_EditStrFilePath(_T(""))
	, m_EditStrLog(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCatPEIDDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_EditStrFilePath);
	DDV_MaxChars(pDX, m_EditStrFilePath, 270);
	DDX_Text(pDX, IDC_EDIT2, m_EditStrLog);
	DDX_Control(pDX, IDC_TAB2, m_Tab);
}

BEGIN_MESSAGE_MAP(CCatPEIDDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BUTTON1, &CCatPEIDDlg::OnBnClickedButton1)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB2, &CCatPEIDDlg::OnTcnSelchangeTab2)
END_MESSAGE_MAP()


// CCatPEIDDlg ��Ϣ�������

BOOL CCatPEIDDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	
	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	AppendLog(L"Cat_Peid 1.0 Welcome !");
	AppendLog(L"ֱ����קĿ�������߿�ݷ�ʽ���� !");
	// UAC ��ק
	ChangeWindowMessageFilter(WM_DROPFILES, MSGFLT_ADD);
	ChangeWindowMessageFilter(WM_COPYDATA, MSGFLT_ADD);
	ChangeWindowMessageFilter(0x0049, MSGFLT_ADD);
	// ��ʼ��TAB�ؼ�
	CRect rs;
	m_Tab.GetClientRect(&rs);
	rs.top += 24;
	rs.bottom -= 3;
	rs.left += 3;
	rs.right -= 5;

	m_Tab.InsertItem(0, L"Section");
	m_Tab.InsertItem(1, L"IAT(�����)");
	m_Tab.InsertItem(2, L"EAT(������)");
	m_Dlg_Section.Create(IDD_SECTION,&m_Tab);
	m_Dlg_Section.MoveWindow(rs);
	m_Dlg_Section.ShowWindow(true);

	m_Dlg_Iat.Create(IDD_IAT, &m_Tab);
	m_Dlg_Iat.MoveWindow(rs);
	m_Dlg_Iat.ShowWindow(false);

	m_Dlg_Eat.Create(IDD_EAT, &m_Tab);
	m_Dlg_Eat.MoveWindow(rs);
	m_Dlg_Eat.ShowWindow(false);

	m_Dlg_Section.m_List_Section.InsertColumn(0, L"������", 0, 100);
	m_Dlg_Section.m_List_Section.InsertColumn(1, L"�ڴ������δ�С", 0, 120);
	m_Dlg_Section.m_List_Section.InsertColumn(2, L"�ڴ���ʼλ��(RVA)", 0, 120);
	m_Dlg_Section.m_List_Section.InsertColumn(3, L"�������ļ���ռ��С", 0, 120);
	m_Dlg_Section.m_List_Section.InsertColumn(4, L"������������ʼλ��", 0, 120);
	m_Dlg_Section.m_List_Section.InsertColumn(5, L"��������", 0, 100);
	m_Dlg_Section.m_List_Section.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	//HTREEITEM hItem = m_Dlg_Iat.m_Tree_Iat.InsertItem(L"root", NULL, NULL);///root���ǽڵ�ı���

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CCatPEIDDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCatPEIDDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CCatPEIDDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCatPEIDDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int DropCount = DragQueryFile(hDropInfo, -1, NULL, 0);//ȡ�ñ��϶��ļ�����Ŀ  
	if(DropCount > 1) {
		AfxMessageBox(L"һ������קһ���ļ���");
	}
	WCHAR wcStr[MAX_PATH] = { 0 };
	DragQueryFile(hDropInfo, 0, wcStr, MAX_PATH);//�����ҷ�ĵ�i���ļ����ļ���
	OnFileGet(wcStr);
	DragFinish(hDropInfo);  //�ϷŽ�����,�ͷ��ڴ�
	CDialogEx::OnDropFiles(hDropInfo);
}


void CCatPEIDDlg::OnBnClickedButton1()
{
	CFileDialog dlg(TRUE,NULL,NULL, OFN_HIDEREADONLY, _T("��ִ���ļ�(*.exe)|*.exe|��̬���ӿ��ļ�(*.dll)|*.dll||"));
	if (dlg.DoModal() == IDOK)
	{
		CString sFilePath = dlg.GetPathName();
		OnFileGet(sFilePath);
	}
}


void CCatPEIDDlg::OnFileGet(CString Path)
{
	if (Path.Find(L".lnk") != -1) {
		Path = ExpandShortcut(Path);
	}
	m_Dlg_Section.m_List_Section.DeleteAllItems();
	m_Dlg_Iat.m_Tree_Iat.DeleteAllItems();
	DWORD TEST = sizeof(IMAGE_DOS_HEADER) + sizeof(IMAGE_NT_HEADERS);
	m_EditStrLog = L"";
	USES_CONVERSION;
	m_EditStrFilePath = Path;
	UpdateData(FALSE);
	CFile fp;
	if (fp.Open(Path, CFile::modeRead | CFile::typeBinary)==0) {
		AfxMessageBox(L"���ļ�ʧ�ܣ������ļ�Ȩ�ޣ�����ʹ�ù���ԱȨ�����У�");
		return;
	}
	auto file_lenth = fp.GetLength();

	IMAGE_DOS_HEADER image_dos_header;
	if (fp.Read(&image_dos_header, sizeof(IMAGE_DOS_HEADER))<sizeof(IMAGE_DOS_HEADER)) {
		//������24�ֽڣ�
		AfxMessageBox(L"�����ļ����������ļ��Ƿ���PE�ļ���");
		return;
	}
	if (image_dos_header.e_magic != 0x5A4D) {
		//��= MZ С���ֽ��򣡣�����
		AfxMessageBox(L"�ļ�ͷ����MZ�����ܲ���PE�ļ���");
		return;
	}
	int ilen_dos = image_dos_header.e_lfanew - sizeof(IMAGE_DOS_HEADER);//DOS�������
	CString temp;
	temp.Format(L"[+] DOS�������0x%x\r\n[+] NTͷƫ��0x%x", ilen_dos,image_dos_header.e_lfanew);
	AppendLog(temp);
	temp = L"[+] DOS������ݣ�";
	CHAR *BUFFER = new CHAR[ilen_dos+1];
	fp.Read(BUFFER, ilen_dos);
	for (int i = 0 ; i < ilen_dos ; i++) {
		CHAR M_C = BUFFER[i];
		if (M_C < 0x21 || M_C > 0x7e ) {
			temp += L".";
		}
		else {
			temp += M_C;
		}
	}
	//AppendLog(temp);
	IMAGE_NT_HEADERS image_nt_headers;
	if (fp.Read(&image_nt_headers, sizeof(IMAGE_NT_HEADERS))<sizeof(IMAGE_NT_HEADERS)) {
		AfxMessageBox(L"����NTͷʧ�ܣ��ļ����ܲ���PE�ļ���");
	}
	if (image_nt_headers.Signature != 0x00004550) {
		//!= PE
		AppendLog(L"PEǩ�������ڣ����ܳ��ִ���");
	}
	temp.Format(L"[+] �ļ���С��0x%llx", file_lenth);
	AppendLog(temp);
	temp.Format(L"[+] �ļ���������Ŀ��%d", image_nt_headers.FileHeader.NumberOfSections);
	AppendLog(temp);
	temp.Format(L"[+] �ļ�����ʱ�䣺"+ unixTime2Str(image_nt_headers.FileHeader.TimeDateStamp));
	AppendLog(temp);
	delete []BUFFER;
	IMAGE_DATA_DIRECTORY Address_IAT, Address_EAT;
	if (image_nt_headers.OptionalHeader.Magic == 0x10B) {
		//32λ�ṹ��
		AppendLog("[+] ������32λ����");

		temp.Format(L"[+] ������ڵ�(RVA)��0x%08x", image_nt_headers.OptionalHeader.AddressOfEntryPoint);
		AppendLog(temp);

		temp.Format(L"[+] �����ַ(Image Base)��0x%08x", image_nt_headers.OptionalHeader.ImageBase);
		AppendLog(temp);

		temp.Format(L"[+] �����С(Image Size)��0x%08x", image_nt_headers.OptionalHeader.SizeOfImage);
		AppendLog(temp);

		temp.Format(L"[+] PEͷ��С(SizeOfHeaders)��0x%08x", image_nt_headers.OptionalHeader.SizeOfHeaders);
		AppendLog(temp);

		switch (image_nt_headers.OptionalHeader.Subsystem)
		{
		case 1:
			temp.Format(L"[+] �ļ��������ļ�");
			break;
		case 2:
			temp.Format(L"[+] �ļ��Ǵ���Ӧ�ó���");
			break;
		case 3:
			temp.Format(L"[+] �ļ��ǿ���̨Ӧ�ó���");
			break;
		default:
			break;
		}
		AppendLog(temp);
		Address_IAT = image_nt_headers.OptionalHeader.DataDirectory[1];
		Address_EAT = image_nt_headers.OptionalHeader.DataDirectory[0];
	} else {
		//64λ�ṹ��
		fp.SeekToBegin();
		int offset = ilen_dos + sizeof(IMAGE_DOS_HEADER);
		fp.Seek(offset, CFile::begin);
		AppendLog("[+] ������64λ����");
		IMAGE_NT_HEADERS64 option;
		fp.Read(&option, sizeof(IMAGE_OPTIONAL_HEADER32));

		temp.Format(L"[+] ������ڵ�(RVA)��0x%08x", option.OptionalHeader.AddressOfEntryPoint);
		AppendLog(temp);

		temp.Format(L"[+] �����ַ(Image Base)��0x%016I64X", option.OptionalHeader.ImageBase);
		AppendLog(temp);

		temp.Format(L"[+] �����С(Image Size)��0x%08x", option.OptionalHeader.SizeOfImage);
		AppendLog(temp);

		temp.Format(L"[+] PEͷ��С(SizeOfHeaders)��0x%08x", option.OptionalHeader.SizeOfHeaders);
		AppendLog(temp);

		switch (option.OptionalHeader.Subsystem)
		{
		case 1:
			temp.Format(L"[+] �ļ��������ļ�");
			break;
		case 2:
			temp.Format(L"[+] �ļ��Ǵ���Ӧ�ó���");
			break;
		case 3:
			temp.Format(L"[+] �ļ��ǿ���̨Ӧ�ó���");
			break;
		default:
			break;
		}
		AppendLog(temp);
		Address_IAT = image_nt_headers.OptionalHeader.DataDirectory[1];
		Address_EAT = image_nt_headers.OptionalHeader.DataDirectory[0];
		//fp.Seek(sizeof(IMAGE_SECTION_HEADER), CFile::current);
	}
	//���IAT,EAT��RVA��ַ
	IMAGE_SECTION_HEADER image_section_header;
	for (int i = 0; i < image_nt_headers.FileHeader.NumberOfSections; i++) {
		fp.Read(&image_section_header, sizeof(IMAGE_SECTION_HEADER));
		m_images.AddTail(image_section_header);//��ӵ�vector��
		CHAR BUFFER[9] = {0};
		memcpy_s(BUFFER, 8, (CHAR*)image_section_header.Name,8);
		CString name(BUFFER);
		int index = m_Dlg_Section.m_List_Section.InsertItem(m_Dlg_Section.m_List_Section.GetItemCount(), name);
		name.Format(L"0x%08x", image_section_header.Misc.VirtualSize);
		m_Dlg_Section.m_List_Section.SetItemText(index, 1, name);//VirtualSize

		name.Format(L"0x%08x", image_section_header.VirtualAddress);
		m_Dlg_Section.m_List_Section.SetItemText(index, 2, name);//VirtualAddress

		name.Format(L"0x%08x", image_section_header.SizeOfRawData);
		m_Dlg_Section.m_List_Section.SetItemText(index, 3, name);//SizeOfRawData

		name.Format(L"0x%08x", image_section_header.PointerToRawData);
		m_Dlg_Section.m_List_Section.SetItemText(index, 4, name);//PointerToRawData

		name.Format(L"0x%08x", image_section_header.Characteristics);
		m_Dlg_Section.m_List_Section.SetItemText(index, 5, name);//Characteristics
	}
	//���IAT����Ϣ
	temp.Format(L"IAT Address:0x%08x Size:%d RAW:0x%08x", Address_IAT.VirtualAddress, Address_IAT.Size, RAV2RAW(Address_IAT.VirtualAddress));
	m_Dlg_Iat.m_Tree_Iat.InsertItem(temp,NULL,NULL);
	//��ʼ��ȡIAT��
	fp.Seek(RAV2RAW(Address_IAT.VirtualAddress), CFile::begin);
	int iCount = Address_IAT.Size / sizeof(IMAGE_IMPORT_DESCRIPTOR);
	IMAGE_IMPORT_DESCRIPTOR *pImage_Imports = new IMAGE_IMPORT_DESCRIPTOR[iCount];
	ZeroMemory(pImage_Imports, sizeof(IMAGE_IMPORT_DESCRIPTOR)*iCount);
	fp.Read(pImage_Imports, Address_IAT.Size);
	//ȫ����ȡ�󣬿�ʼ��������
	for (auto loop_i = 0; loop_i < iCount; loop_i++) {
		DWORD pStrName = pImage_Imports[loop_i].Name;
		pStrName = RAV2RAW(pStrName);
		if (pStrName == 0) {
			break;
		}
		fp.Seek(pStrName, CFile::begin);
		CHAR TEMP_CHAR;
		CString Str_Name = L"";
		//��ȡ����
		while (true)
		{
			fp.Read(&TEMP_CHAR, sizeof(CHAR));
			if (TEMP_CHAR == '\0') {
				break;
			}
			Str_Name += TEMP_CHAR;
		}
		auto index = m_Dlg_Iat.m_Tree_Iat.InsertItem(Str_Name, NULL, NULL);
		//��ȡ���ƽ��������濪ʼ��ȡÿ������
		DWORD offset_function = RAV2RAW(pImage_Imports[loop_i].OriginalFirstThunk);
		fp.Seek(offset_function, CFile::begin);
		IMAGE_IMPORT_BY_NAME image_import_by_name;
		std::vector<DWORD> m_pINTS;//ָ��ÿ��INT����ָ��
		while (true) {
			DWORD pINT;
			fp.Read(&pINT, sizeof(DWORD));
			if (pINT == NULL) {
				break;
			}
			m_pINTS.push_back(RAV2RAW(pINT));
		}
		for (auto v : m_pINTS) {
			if (v == 0) {
				continue;
			}
			fp.Seek(v,CFile::begin);
			fp.Read(&image_import_by_name, sizeof(IMAGE_IMPORT_BY_NAME));
			if (image_import_by_name.Hint == NULL) {
				continue;
			}
			fp.Seek(-1, CFile::current);
			CString Function_Name;
			Function_Name = L"";
			if (image_import_by_name.Name[0] != '\0') {
				Function_Name += image_import_by_name.Name[0];
			}
			while (true)
			{
				fp.Read(&TEMP_CHAR, sizeof(CHAR));
				if (TEMP_CHAR == '\0') {
					break;
				}
				Function_Name += TEMP_CHAR;
			}
			CString Hint;
			Hint.Format(L" Hint:%d", image_import_by_name.Hint);
			Function_Name += Hint;
			m_Dlg_Iat.m_Tree_Iat.InsertItem(Function_Name, NULL, NULL, index);
		}
	

	}

	//���EAT��
	temp.Format(L"[+] EAT Address:0x%08x Size:%d RAW:0x%08x", Address_EAT.VirtualAddress, Address_EAT.Size, RAV2RAW(Address_EAT.VirtualAddress));
	if (Address_EAT.VirtualAddress != 0) {
		//���ڵ����
		fp.Seek(RAV2RAW(Address_EAT.VirtualAddress), CFile::begin);
		IMAGE_EXPORT_DIRECTORY image_export_directory;
		fp.Read(&image_export_directory, sizeof(IMAGE_EXPORT_DIRECTORY));
		fp.Seek(RAV2RAW(image_export_directory.Name), CFile::begin);
		CHAR TEMP_CHAR;
		CString ModuleName = L"";
		while (true)
		{
			fp.Read(&TEMP_CHAR, sizeof(CHAR));
			if (TEMP_CHAR == '\0') {
				break;
			}
			ModuleName += TEMP_CHAR;
		}
		auto index = m_Dlg_Eat.m_Tree_Eat.InsertItem(ModuleName, NULL, NULL);//�����
		int temp_offset = RAV2RAW(image_export_directory.AddressOfNames);
		fp.Seek(temp_offset, CFile::begin);
		std::vector<DWORD>m_dires;
		for (unsigned int Ncount = 0; Ncount < (image_export_directory.NumberOfNames); Ncount++) {
			DWORD temp_dword;
			fp.Read(&temp_dword, sizeof(DWORD));
			m_dires.push_back(RAV2RAW(temp_dword));
		}
		CString Function_Name;
		for (auto t_v : m_dires) {
			fp.Seek(t_v, CFile::begin);
			Function_Name = L"";
			while (true)
			{
				fp.Read(&TEMP_CHAR, sizeof(CHAR));
				if (TEMP_CHAR == '\0') {
					break;
				}
				Function_Name += TEMP_CHAR;
			}
			m_Dlg_Eat.m_Tree_Eat.InsertItem(Function_Name, NULL, NULL, index);
		}
	}
	fp.Close();
}


void CCatPEIDDlg::AppendLog(CString Text)
{
	m_EditStrLog += Text+L"\r\n";
	UpdateData(FALSE);
}
void CCatPEIDDlg::AppendLog(LPSTR Text)
{
	CString temp(Text);
	m_EditStrLog += temp + L"\r\n";
	UpdateData(FALSE);
}
CString unixTime2Str(DWORD n)
{
	time_t m_t = n;
	tm *p_tm = gmtime(&m_t);
	CHAR BUFFER[1024];
	strftime(BUFFER, 1024 - 1, "%Y-%m-%d %H:%M:%S", p_tm);
	CString ret(BUFFER);
	return ret;
}
CString ExpandShortcut(CString &inFile)
{
	CString   outFile = _T(" ");
	ASSERT(inFile != _T(""));
	IShellLink*   psl;
	HRESULT   hres;
	LPTSTR   lpsz = inFile.GetBuffer(MAX_PATH);
	hres = ::CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER,
		IID_IShellLink, (LPVOID*)&psl);
	if (SUCCEEDED(hres)) {
		IPersistFile*   ppf;
		hres = psl->QueryInterface(IID_IPersistFile, (LPVOID*)&ppf);
		if (SUCCEEDED(hres)) {
#ifndef _UNICODE
			wchar_t   wsz[MAX_PATH];
			::MultiByteToWideChar(CP_ACP, 0, lpsz, -1, wsz, MAX_PATH);
			hres = ppf->Load(wsz, STGM_READ);
#else
			hres = ppf->Load(lpsz, STGM_READ);
#endif
			if (SUCCEEDED(hres)) {
				WIN32_FIND_DATA   wfd;
				//   find   the   path   from   that
				HRESULT   hres = psl->GetPath(outFile.GetBuffer(MAX_PATH),
					MAX_PATH,
					&wfd,
					SLGP_UNCPRIORITY);

				outFile.ReleaseBuffer();
			}
			ppf->Release();
		}
		psl->Release();
	}
	inFile.ReleaseBuffer();
	return   outFile;
}

void CCatPEIDDlg::OnTcnSelchangeTab2(NMHDR *pNMHDR, LRESULT *pResult)
{
	switch (m_Tab.GetCurSel())
	{
	case 0:
		m_Dlg_Section.ShowWindow(true);
		m_Dlg_Iat.ShowWindow(false);
		m_Dlg_Eat.ShowWindow(false);
		break;
	case 1:
		m_Dlg_Section.ShowWindow(false);
		m_Dlg_Iat.ShowWindow(true);
		m_Dlg_Eat.ShowWindow(false);
		break;
	case 2:
		m_Dlg_Section.ShowWindow(false);
		m_Dlg_Iat.ShowWindow(false);
		m_Dlg_Eat.ShowWindow(true);
		break;
	}
	*pResult = 0;
}

DWORD CCatPEIDDlg::RAV2RAW(DWORD Rav)
{
	if (Rav == 0) {
		return 0;
	}
	POSITION pos = m_images.GetHeadPosition();
	while (pos != NULL)
	{
		auto ptr = m_images.GetNext(pos);
		if (ptr.VirtualAddress<Rav && ptr.VirtualAddress + ptr.Misc.VirtualSize > Rav) {
			DWORD Ret;
			Ret = Rav - ptr.VirtualAddress + ptr.PointerToRawData;
			return Ret;
		}
	}
	//throw "Invalid Rav Conversion!";
	return NULL;
}
