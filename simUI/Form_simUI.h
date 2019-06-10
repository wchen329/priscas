﻿#pragma once
#include <cstdio>
#include "CPUSelectDialog.h"
#include "memorySizeDialog.h"
#include "Form_About.h"

namespace simUI {
	
	
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Resources;

	/// <summary>
	/// Main window for simUI
	/// </summary>
	public ref class Form_simUI : public System::Windows::Forms::Form
	{
		public:
			Form_simUI(void)
			{
				cpu_type = 0;
				mem_bits = 16;
				cpusd = gcnew CPUSelectDialog();
				memsd = gcnew memorySizeDialog();
				InitializeComponent();
			}
	
		protected:
		private: int cpu_type;
		private: int mem_bits;
		private: CPUSelectDialog^ cpusd;
		private: memorySizeDialog^ memsd;
		private: System::Windows::Forms::MenuStrip^  menuStrip_main;
		private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  helpToolStripMenuItem;
		private: System::Windows::Forms::StatusStrip^  statusStripMain;
		private: System::Windows::Forms::ToolStripMenuItem^  aboutToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  toolsToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  editToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  projectToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  simulationToolStripMenuItem;
		private: System::Windows::Forms::ToolStrip^  toolStripSimulation;
		private: System::Windows::Forms::ToolStrip^  toolStripIO;
		private: System::Windows::Forms::ToolStripMenuItem^  viewToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  toolbarsToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  iOBarToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  simulationToolbarToolStripMenuItem;
		private: System::Windows::Forms::FontDialog^  fontDialogTextEditor;
		private: System::Windows::Forms::SplitContainer^  splitContainerMain;
		private: System::Windows::Forms::SplitContainer^  splitContainerTextConsole;
		private: System::Windows::Forms::TabControl^  tabControlSidepane;
		private: System::Windows::Forms::TabPage^  tabPageProjectExp;
		private: System::Windows::Forms::TabPage^  tabPageRecFiles;
		private: System::Windows::Forms::RichTextBox^  richTextBoxConsole;
		private: System::Windows::Forms::ToolStripButton^  toolStripButtonSimulate;
		private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;
		private: System::Diagnostics::Process^  processSimulation;
		private: System::Windows::Forms::ToolStripButton^  toolStripButtonRunDirective;
		private: System::Windows::Forms::ToolTip^  toolTip1;
		private: System::Windows::Forms::OpenFileDialog^  openFileDialogASMSource;
		private: System::Windows::Forms::ToolStripButton^  toolStripButtonStop;
		private: System::Windows::Forms::TabControl^  tabControlMain;
		private: System::Windows::Forms::TabPage^  tabPageTextEdit;
		private: System::Windows::Forms::RichTextBox^  richTextBoxTextEditor;
		private: System::Windows::Forms::ToolStripMenuItem^  openToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  assemblySourceToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  projentToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  cPUTypeSelectionToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  clearConsoleInputToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  fToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  consoleFontToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  textEditorFontToolStripMenuItem;
		private: System::Windows::Forms::FontDialog^  fontDialogConsole;
		private: System::Windows::Forms::ToolStripMenuItem^  copyToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  cutToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  pasteToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  memorySizeToolStripMenuItem;
		private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;
		private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator2;
		private: System::Windows::Forms::ToolStripMenuItem^  openToolStripMenuItem1;
		private: System::Windows::Forms::ToolStripMenuItem^  registerStatesToolStripMenuItem;
		private: System::Windows::Forms::Label^  labelProjWarn;
		private: System::Windows::Forms::ListView^  listViewRecentFiles;
		private: System::Windows::Forms::ToolStripButton^  toolStripButtonBreakExecution;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItemSaveASMAs;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItemSaveProject;





		private: System::Windows::Forms::ToolStripButton^  toolStripButtonOpen;
		private: System::Windows::Forms::ToolStripButton^  toolStripButtonNew;
		private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator3;
		private: System::Windows::Forms::ToolStripButton^  toolStripButtonNewProject;
		private: System::Windows::Forms::ToolStripButton^  toolStripButtonOpenProject;
		private: System::Windows::Forms::ToolStripButton^  toolStripButtonSave;
		private: System::Windows::Forms::ToolStripButton^  toolStripButtonSaveProject;
		private: System::Windows::Forms::ToolStripButton^  toolStripButtonCut;
		private: System::Windows::Forms::ToolStripButton^  toolStripButtonCopy;
		private: System::Windows::Forms::ToolStripButton^  toolStripButtonPaste;
		private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator4;
		private: System::Windows::Forms::ToolStripButton^  toolStripButtonUndo;
		private: System::Windows::Forms::ToolStripButton^  toolStripButtonRedo;
		private: System::IO::Ports::SerialPort^  serialPort1;
	private: System::Windows::Forms::ContextMenuStrip^  contextMenuStripTextEditor;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItemCut;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItemCopy;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItemPaste;
	private: System::Windows::Forms::ToolStripMenuItem^  newToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  assemblySourceToolStripMenuItemNewASM;
	private: System::Windows::Forms::ToolStripMenuItem^  projectToolStripMenuItemNewProj;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItemSaveASM;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator5;
	private: System::Windows::Forms::ToolStripMenuItem^  undoToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  redoToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator6;

	private: System::ComponentModel::IContainer^  components;

		protected: 

		private:

			void reinitProc()
			{
				this->processSimulation->StartInfo->Domain = L"";
				this->processSimulation->StartInfo->LoadUserProfile = false;
				this->processSimulation->StartInfo->Password = nullptr;
				this->processSimulation->StartInfo->StandardErrorEncoding = nullptr;
				this->processSimulation->StartInfo->StandardOutputEncoding = nullptr;
				this->processSimulation->StartInfo->UserName = L"";
				this->processSimulation->SynchronizingObject = this;
				this->processSimulation->OutputDataReceived += gcnew System::Diagnostics::DataReceivedEventHandler(this, &Form_simUI::processSimulation_OutputDataReceived);
				this->processSimulation->ErrorDataReceived += gcnew System::Diagnostics::DataReceivedEventHandler(this, &Form_simUI::processSimulation_ErrorDataReceived);
				this->processSimulation->Exited += gcnew System::EventHandler(this, &Form_simUI::processSimulation_Exited);
			}

			/// <summary>
			/// Required designer variable.
			/// </summary>


#pragma region Windows Form Designer generated code
			/// <summary>
			/// Required method for Designer support - do not modify
			/// the contents of this method with the code editor.
			/// </summary>
			void InitializeComponent(void)
			{
				this->components = (gcnew System::ComponentModel::Container());
				System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form_simUI::typeid));
				this->menuStrip_main = (gcnew System::Windows::Forms::MenuStrip());
				this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->newToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->assemblySourceToolStripMenuItemNewASM = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->projectToolStripMenuItemNewProj = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->assemblySourceToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->projentToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->toolStripSeparator5 = (gcnew System::Windows::Forms::ToolStripSeparator());
				this->toolStripMenuItemSaveASM = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->toolStripMenuItemSaveASMAs = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->toolStripMenuItemSaveProject = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
				this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->editToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->copyToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->cutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->pasteToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->toolStripSeparator6 = (gcnew System::Windows::Forms::ToolStripSeparator());
				this->undoToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->redoToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->projectToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->simulationToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->memorySizeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->cPUTypeSelectionToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->viewToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->fToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->consoleFontToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->textEditorFontToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->toolStripSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
				this->clearConsoleInputToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->toolbarsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->iOBarToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->simulationToolbarToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->toolsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->openToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->registerStatesToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->helpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->aboutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->statusStripMain = (gcnew System::Windows::Forms::StatusStrip());
				this->toolStripSimulation = (gcnew System::Windows::Forms::ToolStrip());
				this->toolStripButtonSimulate = (gcnew System::Windows::Forms::ToolStripButton());
				this->toolStripButtonRunDirective = (gcnew System::Windows::Forms::ToolStripButton());
				this->toolStripButtonStop = (gcnew System::Windows::Forms::ToolStripButton());
				this->toolStripButtonBreakExecution = (gcnew System::Windows::Forms::ToolStripButton());
				this->toolStripIO = (gcnew System::Windows::Forms::ToolStrip());
				this->toolStripButtonNew = (gcnew System::Windows::Forms::ToolStripButton());
				this->toolStripButtonNewProject = (gcnew System::Windows::Forms::ToolStripButton());
				this->toolStripButtonOpen = (gcnew System::Windows::Forms::ToolStripButton());
				this->toolStripButtonOpenProject = (gcnew System::Windows::Forms::ToolStripButton());
				this->toolStripButtonSave = (gcnew System::Windows::Forms::ToolStripButton());
				this->toolStripButtonSaveProject = (gcnew System::Windows::Forms::ToolStripButton());
				this->toolStripSeparator3 = (gcnew System::Windows::Forms::ToolStripSeparator());
				this->toolStripButtonCut = (gcnew System::Windows::Forms::ToolStripButton());
				this->toolStripButtonCopy = (gcnew System::Windows::Forms::ToolStripButton());
				this->toolStripButtonPaste = (gcnew System::Windows::Forms::ToolStripButton());
				this->toolStripSeparator4 = (gcnew System::Windows::Forms::ToolStripSeparator());
				this->toolStripButtonUndo = (gcnew System::Windows::Forms::ToolStripButton());
				this->toolStripButtonRedo = (gcnew System::Windows::Forms::ToolStripButton());
				this->fontDialogTextEditor = (gcnew System::Windows::Forms::FontDialog());
				this->splitContainerMain = (gcnew System::Windows::Forms::SplitContainer());
				this->tabControlSidepane = (gcnew System::Windows::Forms::TabControl());
				this->tabPageProjectExp = (gcnew System::Windows::Forms::TabPage());
				this->labelProjWarn = (gcnew System::Windows::Forms::Label());
				this->tabPageRecFiles = (gcnew System::Windows::Forms::TabPage());
				this->listViewRecentFiles = (gcnew System::Windows::Forms::ListView());
				this->splitContainerTextConsole = (gcnew System::Windows::Forms::SplitContainer());
				this->tabControlMain = (gcnew System::Windows::Forms::TabControl());
				this->tabPageTextEdit = (gcnew System::Windows::Forms::TabPage());
				this->richTextBoxTextEditor = (gcnew System::Windows::Forms::RichTextBox());
				this->contextMenuStripTextEditor = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
				this->toolStripMenuItemCut = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->toolStripMenuItemCopy = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->toolStripMenuItemPaste = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->richTextBoxConsole = (gcnew System::Windows::Forms::RichTextBox());
				this->processSimulation = (gcnew System::Diagnostics::Process());
				this->toolTip1 = (gcnew System::Windows::Forms::ToolTip(this->components));
				this->openFileDialogASMSource = (gcnew System::Windows::Forms::OpenFileDialog());
				this->fontDialogConsole = (gcnew System::Windows::Forms::FontDialog());
				this->serialPort1 = (gcnew System::IO::Ports::SerialPort(this->components));
				this->menuStrip_main->SuspendLayout();
				this->toolStripSimulation->SuspendLayout();
				this->toolStripIO->SuspendLayout();
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->splitContainerMain))->BeginInit();
				this->splitContainerMain->Panel1->SuspendLayout();
				this->splitContainerMain->Panel2->SuspendLayout();
				this->splitContainerMain->SuspendLayout();
				this->tabControlSidepane->SuspendLayout();
				this->tabPageProjectExp->SuspendLayout();
				this->tabPageRecFiles->SuspendLayout();
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->splitContainerTextConsole))->BeginInit();
				this->splitContainerTextConsole->Panel1->SuspendLayout();
				this->splitContainerTextConsole->Panel2->SuspendLayout();
				this->splitContainerTextConsole->SuspendLayout();
				this->tabControlMain->SuspendLayout();
				this->tabPageTextEdit->SuspendLayout();
				this->contextMenuStripTextEditor->SuspendLayout();
				this->SuspendLayout();
				// 
				// menuStrip_main
				// 
				this->menuStrip_main->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(7) {this->fileToolStripMenuItem, 
					this->editToolStripMenuItem, this->projectToolStripMenuItem, this->simulationToolStripMenuItem, this->viewToolStripMenuItem, 
					this->toolsToolStripMenuItem, this->helpToolStripMenuItem});
				this->menuStrip_main->Location = System::Drawing::Point(0, 0);
				this->menuStrip_main->Name = L"menuStrip_main";
				this->menuStrip_main->Size = System::Drawing::Size(993, 24);
				this->menuStrip_main->TabIndex = 0;
				this->menuStrip_main->Text = L"menuStrip";
				// 
				// fileToolStripMenuItem
				// 
				this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(8) {this->newToolStripMenuItem, 
					this->openToolStripMenuItem, this->toolStripSeparator5, this->toolStripMenuItemSaveASM, this->toolStripMenuItemSaveASMAs, this->toolStripMenuItemSaveProject, 
					this->toolStripSeparator1, this->exitToolStripMenuItem});
				this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
				this->fileToolStripMenuItem->Size = System::Drawing::Size(37, 20);
				this->fileToolStripMenuItem->Text = L"File";
				// 
				// newToolStripMenuItem
				// 
				this->newToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->assemblySourceToolStripMenuItemNewASM, 
					this->projectToolStripMenuItemNewProj});
				this->newToolStripMenuItem->Name = L"newToolStripMenuItem";
				this->newToolStripMenuItem->Size = System::Drawing::Size(187, 22);
				this->newToolStripMenuItem->Text = L"New";
				// 
				// assemblySourceToolStripMenuItemNewASM
				// 
				this->assemblySourceToolStripMenuItemNewASM->Name = L"assemblySourceToolStripMenuItemNewASM";
				this->assemblySourceToolStripMenuItemNewASM->Size = System::Drawing::Size(173, 22);
				this->assemblySourceToolStripMenuItemNewASM->Text = L"Assembly Source...";
				// 
				// projectToolStripMenuItemNewProj
				// 
				this->projectToolStripMenuItemNewProj->Enabled = false;
				this->projectToolStripMenuItemNewProj->Name = L"projectToolStripMenuItemNewProj";
				this->projectToolStripMenuItemNewProj->Size = System::Drawing::Size(173, 22);
				this->projectToolStripMenuItemNewProj->Text = L"Project...";
				// 
				// openToolStripMenuItem
				// 
				this->openToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->assemblySourceToolStripMenuItem, 
					this->projentToolStripMenuItem});
				this->openToolStripMenuItem->Name = L"openToolStripMenuItem";
				this->openToolStripMenuItem->Size = System::Drawing::Size(187, 22);
				this->openToolStripMenuItem->Text = L"Open";
				// 
				// assemblySourceToolStripMenuItem
				// 
				this->assemblySourceToolStripMenuItem->Name = L"assemblySourceToolStripMenuItem";
				this->assemblySourceToolStripMenuItem->Size = System::Drawing::Size(173, 22);
				this->assemblySourceToolStripMenuItem->Text = L"Assembly Source...";
				this->assemblySourceToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form_simUI::assemblySourceToolStripMenuItem_Click);
				// 
				// projentToolStripMenuItem
				// 
				this->projentToolStripMenuItem->Enabled = false;
				this->projentToolStripMenuItem->Name = L"projentToolStripMenuItem";
				this->projentToolStripMenuItem->Size = System::Drawing::Size(173, 22);
				this->projentToolStripMenuItem->Text = L"Project...";
				// 
				// toolStripSeparator5
				// 
				this->toolStripSeparator5->Name = L"toolStripSeparator5";
				this->toolStripSeparator5->Size = System::Drawing::Size(184, 6);
				// 
				// toolStripMenuItemSaveASM
				// 
				this->toolStripMenuItemSaveASM->Name = L"toolStripMenuItemSaveASM";
				this->toolStripMenuItemSaveASM->Size = System::Drawing::Size(187, 22);
				this->toolStripMenuItemSaveASM->Text = L"Save Current File";
				// 
				// toolStripMenuItemSaveASMAs
				// 
				this->toolStripMenuItemSaveASMAs->Name = L"toolStripMenuItemSaveASMAs";
				this->toolStripMenuItemSaveASMAs->Size = System::Drawing::Size(187, 22);
				this->toolStripMenuItemSaveASMAs->Text = L"Save Current File As...";
				// 
				// toolStripMenuItemSaveProject
				// 
				this->toolStripMenuItemSaveProject->Enabled = false;
				this->toolStripMenuItemSaveProject->Name = L"toolStripMenuItemSaveProject";
				this->toolStripMenuItemSaveProject->Size = System::Drawing::Size(187, 22);
				this->toolStripMenuItemSaveProject->Text = L"Save Project";
				// 
				// toolStripSeparator1
				// 
				this->toolStripSeparator1->Name = L"toolStripSeparator1";
				this->toolStripSeparator1->Size = System::Drawing::Size(184, 6);
				// 
				// exitToolStripMenuItem
				// 
				this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
				this->exitToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Alt | System::Windows::Forms::Keys::F4));
				this->exitToolStripMenuItem->Size = System::Drawing::Size(187, 22);
				this->exitToolStripMenuItem->Text = L"Exit";
				this->exitToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form_simUI::exitToolStripMenuItem_Click);
				// 
				// editToolStripMenuItem
				// 
				this->editToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {this->copyToolStripMenuItem, 
					this->cutToolStripMenuItem, this->pasteToolStripMenuItem, this->toolStripSeparator6, this->undoToolStripMenuItem, this->redoToolStripMenuItem});
				this->editToolStripMenuItem->Name = L"editToolStripMenuItem";
				this->editToolStripMenuItem->Size = System::Drawing::Size(39, 20);
				this->editToolStripMenuItem->Text = L"Edit";
				// 
				// copyToolStripMenuItem
				// 
				this->copyToolStripMenuItem->Name = L"copyToolStripMenuItem";
				this->copyToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::C));
				this->copyToolStripMenuItem->Size = System::Drawing::Size(152, 22);
				this->copyToolStripMenuItem->Text = L"Copy";
				this->copyToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form_simUI::copyToolStripMenuItem_Click);
				// 
				// cutToolStripMenuItem
				// 
				this->cutToolStripMenuItem->Name = L"cutToolStripMenuItem";
				this->cutToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::X));
				this->cutToolStripMenuItem->Size = System::Drawing::Size(152, 22);
				this->cutToolStripMenuItem->Text = L"Cut";
				this->cutToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form_simUI::cutToolStripMenuItem_Click);
				// 
				// pasteToolStripMenuItem
				// 
				this->pasteToolStripMenuItem->Name = L"pasteToolStripMenuItem";
				this->pasteToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::V));
				this->pasteToolStripMenuItem->Size = System::Drawing::Size(152, 22);
				this->pasteToolStripMenuItem->Text = L"Paste";
				this->pasteToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form_simUI::pasteToolStripMenuItem_Click);
				// 
				// toolStripSeparator6
				// 
				this->toolStripSeparator6->Name = L"toolStripSeparator6";
				this->toolStripSeparator6->Size = System::Drawing::Size(149, 6);
				// 
				// undoToolStripMenuItem
				// 
				this->undoToolStripMenuItem->Name = L"undoToolStripMenuItem";
				this->undoToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::Z));
				this->undoToolStripMenuItem->Size = System::Drawing::Size(152, 22);
				this->undoToolStripMenuItem->Text = L"Undo";
				this->undoToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form_simUI::undoToolStripMenuItem_Click);
				// 
				// redoToolStripMenuItem
				// 
				this->redoToolStripMenuItem->Name = L"redoToolStripMenuItem";
				this->redoToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::Y));
				this->redoToolStripMenuItem->Size = System::Drawing::Size(152, 22);
				this->redoToolStripMenuItem->Text = L"Redo";
				this->redoToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form_simUI::redoToolStripMenuItem_Click);
				// 
				// projectToolStripMenuItem
				// 
				this->projectToolStripMenuItem->Enabled = false;
				this->projectToolStripMenuItem->Name = L"projectToolStripMenuItem";
				this->projectToolStripMenuItem->Size = System::Drawing::Size(56, 20);
				this->projectToolStripMenuItem->Text = L"Project";
				// 
				// simulationToolStripMenuItem
				// 
				this->simulationToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->memorySizeToolStripMenuItem, 
					this->cPUTypeSelectionToolStripMenuItem});
				this->simulationToolStripMenuItem->Name = L"simulationToolStripMenuItem";
				this->simulationToolStripMenuItem->Size = System::Drawing::Size(76, 20);
				this->simulationToolStripMenuItem->Text = L"Simulation";
				// 
				// memorySizeToolStripMenuItem
				// 
				this->memorySizeToolStripMenuItem->Name = L"memorySizeToolStripMenuItem";
				this->memorySizeToolStripMenuItem->Size = System::Drawing::Size(177, 22);
				this->memorySizeToolStripMenuItem->Text = L"Memory Size";
				this->memorySizeToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form_simUI::memorySizeToolStripMenuItem_Click);
				// 
				// cPUTypeSelectionToolStripMenuItem
				// 
				this->cPUTypeSelectionToolStripMenuItem->Name = L"cPUTypeSelectionToolStripMenuItem";
				this->cPUTypeSelectionToolStripMenuItem->Size = System::Drawing::Size(177, 22);
				this->cPUTypeSelectionToolStripMenuItem->Text = L"CPU Type Selection";
				this->cPUTypeSelectionToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form_simUI::cPUTypeSelectionToolStripMenuItem_Click);
				// 
				// viewToolStripMenuItem
				// 
				this->viewToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {this->fToolStripMenuItem, 
					this->toolStripSeparator2, this->clearConsoleInputToolStripMenuItem, this->toolbarsToolStripMenuItem});
				this->viewToolStripMenuItem->Name = L"viewToolStripMenuItem";
				this->viewToolStripMenuItem->Size = System::Drawing::Size(44, 20);
				this->viewToolStripMenuItem->Text = L"View";
				// 
				// fToolStripMenuItem
				// 
				this->fToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->consoleFontToolStripMenuItem, 
					this->textEditorFontToolStripMenuItem});
				this->fToolStripMenuItem->Name = L"fToolStripMenuItem";
				this->fToolStripMenuItem->Size = System::Drawing::Size(188, 22);
				this->fToolStripMenuItem->Text = L"Font...";
				// 
				// consoleFontToolStripMenuItem
				// 
				this->consoleFontToolStripMenuItem->Name = L"consoleFontToolStripMenuItem";
				this->consoleFontToolStripMenuItem->Size = System::Drawing::Size(157, 22);
				this->consoleFontToolStripMenuItem->Text = L"Console Font";
				this->consoleFontToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form_simUI::consoleFontToolStripMenuItem_Click);
				// 
				// textEditorFontToolStripMenuItem
				// 
				this->textEditorFontToolStripMenuItem->Name = L"textEditorFontToolStripMenuItem";
				this->textEditorFontToolStripMenuItem->Size = System::Drawing::Size(157, 22);
				this->textEditorFontToolStripMenuItem->Text = L"Text Editor Font";
				this->textEditorFontToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form_simUI::textEditorFontToolStripMenuItem_Click);
				// 
				// toolStripSeparator2
				// 
				this->toolStripSeparator2->Name = L"toolStripSeparator2";
				this->toolStripSeparator2->Size = System::Drawing::Size(185, 6);
				// 
				// clearConsoleInputToolStripMenuItem
				// 
				this->clearConsoleInputToolStripMenuItem->Name = L"clearConsoleInputToolStripMenuItem";
				this->clearConsoleInputToolStripMenuItem->Size = System::Drawing::Size(188, 22);
				this->clearConsoleInputToolStripMenuItem->Text = L"Clear Console Output";
				this->clearConsoleInputToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form_simUI::clearConsoleInputToolStripMenuItem_Click);
				// 
				// toolbarsToolStripMenuItem
				// 
				this->toolbarsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->iOBarToolStripMenuItem, 
					this->simulationToolbarToolStripMenuItem});
				this->toolbarsToolStripMenuItem->Name = L"toolbarsToolStripMenuItem";
				this->toolbarsToolStripMenuItem->Size = System::Drawing::Size(188, 22);
				this->toolbarsToolStripMenuItem->Text = L"Toolbars...";
				// 
				// iOBarToolStripMenuItem
				// 
				this->iOBarToolStripMenuItem->Checked = true;
				this->iOBarToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
				this->iOBarToolStripMenuItem->Name = L"iOBarToolStripMenuItem";
				this->iOBarToolStripMenuItem->Size = System::Drawing::Size(175, 22);
				this->iOBarToolStripMenuItem->Text = L"I/O Toolbar";
				this->iOBarToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form_simUI::iOBarToolStripMenuItem_Click);
				// 
				// simulationToolbarToolStripMenuItem
				// 
				this->simulationToolbarToolStripMenuItem->Checked = true;
				this->simulationToolbarToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
				this->simulationToolbarToolStripMenuItem->Name = L"simulationToolbarToolStripMenuItem";
				this->simulationToolbarToolStripMenuItem->Size = System::Drawing::Size(175, 22);
				this->simulationToolbarToolStripMenuItem->Text = L"Simulation Toolbar";
				this->simulationToolbarToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form_simUI::simulationToolbarToolStripMenuItem_Click);
				// 
				// toolsToolStripMenuItem
				// 
				this->toolsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->openToolStripMenuItem1, 
					this->registerStatesToolStripMenuItem});
				this->toolsToolStripMenuItem->Name = L"toolsToolStripMenuItem";
				this->toolsToolStripMenuItem->Size = System::Drawing::Size(48, 20);
				this->toolsToolStripMenuItem->Text = L"Tools";
				// 
				// openToolStripMenuItem1
				// 
				this->openToolStripMenuItem1->Name = L"openToolStripMenuItem1";
				this->openToolStripMenuItem1->Size = System::Drawing::Size(171, 22);
				this->openToolStripMenuItem1->Text = L"Memory Inspector";
				// 
				// registerStatesToolStripMenuItem
				// 
				this->registerStatesToolStripMenuItem->Name = L"registerStatesToolStripMenuItem";
				this->registerStatesToolStripMenuItem->Size = System::Drawing::Size(171, 22);
				this->registerStatesToolStripMenuItem->Text = L"Register States";
				// 
				// helpToolStripMenuItem
				// 
				this->helpToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->aboutToolStripMenuItem});
				this->helpToolStripMenuItem->Name = L"helpToolStripMenuItem";
				this->helpToolStripMenuItem->Size = System::Drawing::Size(44, 20);
				this->helpToolStripMenuItem->Text = L"Help";
				// 
				// aboutToolStripMenuItem
				// 
				this->aboutToolStripMenuItem->Name = L"aboutToolStripMenuItem";
				this->aboutToolStripMenuItem->Size = System::Drawing::Size(107, 22);
				this->aboutToolStripMenuItem->Text = L"About";
				this->aboutToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form_simUI::aboutToolStripMenuItem_Click);
				// 
				// statusStripMain
				// 
				this->statusStripMain->Location = System::Drawing::Point(0, 554);
				this->statusStripMain->Name = L"statusStripMain";
				this->statusStripMain->Size = System::Drawing::Size(993, 22);
				this->statusStripMain->TabIndex = 3;
				this->statusStripMain->Text = L"statusStrip1";
				// 
				// toolStripSimulation
				// 
				this->toolStripSimulation->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
				this->toolStripSimulation->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {this->toolStripButtonSimulate, 
					this->toolStripButtonRunDirective, this->toolStripButtonStop, this->toolStripButtonBreakExecution});
				this->toolStripSimulation->Location = System::Drawing::Point(0, 49);
				this->toolStripSimulation->Name = L"toolStripSimulation";
				this->toolStripSimulation->Size = System::Drawing::Size(993, 25);
				this->toolStripSimulation->TabIndex = 2;
				// 
				// toolStripButtonSimulate
				// 
				this->toolStripButtonSimulate->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
				this->toolStripButtonSimulate->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->toolStripButtonSimulate->Name = L"toolStripButtonSimulate";
				this->toolStripButtonSimulate->Size = System::Drawing::Size(57, 22);
				this->toolStripButtonSimulate->Text = L"Simulate";
				this->toolStripButtonSimulate->Click += gcnew System::EventHandler(this, &Form_simUI::toolStripButtonSimulate_Click);
				// 
				// toolStripButtonRunDirective
				// 
				this->toolStripButtonRunDirective->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
				this->toolStripButtonRunDirective->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->toolStripButtonRunDirective->Name = L"toolStripButtonRunDirective";
				this->toolStripButtonRunDirective->Size = System::Drawing::Size(81, 22);
				this->toolStripButtonRunDirective->Text = L"Run Directive";
				// 
				// toolStripButtonStop
				// 
				this->toolStripButtonStop->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
				this->toolStripButtonStop->Enabled = false;
				this->toolStripButtonStop->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->toolStripButtonStop->Name = L"toolStripButtonStop";
				this->toolStripButtonStop->Size = System::Drawing::Size(95, 22);
				this->toolStripButtonStop->Text = L"Stop Simulation";
				this->toolStripButtonStop->Click += gcnew System::EventHandler(this, &Form_simUI::toolStripButtonStop_Click);
				// 
				// toolStripButtonBreakExecution
				// 
				this->toolStripButtonBreakExecution->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
				this->toolStripButtonBreakExecution->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->toolStripButtonBreakExecution->Name = L"toolStripButtonBreakExecution";
				this->toolStripButtonBreakExecution->Size = System::Drawing::Size(94, 22);
				this->toolStripButtonBreakExecution->Text = L"Break Execution";
				// 
				// toolStripIO
				// 
				this->toolStripIO->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
				this->toolStripIO->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(13) {this->toolStripButtonNew, 
					this->toolStripButtonNewProject, this->toolStripButtonOpen, this->toolStripButtonOpenProject, this->toolStripButtonSave, this->toolStripButtonSaveProject, 
					this->toolStripSeparator3, this->toolStripButtonCut, this->toolStripButtonCopy, this->toolStripButtonPaste, this->toolStripSeparator4, 
					this->toolStripButtonUndo, this->toolStripButtonRedo});
				this->toolStripIO->Location = System::Drawing::Point(0, 24);
				this->toolStripIO->Name = L"toolStripIO";
				this->toolStripIO->Size = System::Drawing::Size(993, 25);
				this->toolStripIO->TabIndex = 1;
				// 
				// toolStripButtonNew
				// 
				this->toolStripButtonNew->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->toolStripButtonNew->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButtonNew.Image")));
				this->toolStripButtonNew->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->toolStripButtonNew->Name = L"toolStripButtonNew";
				this->toolStripButtonNew->Size = System::Drawing::Size(23, 22);
				this->toolStripButtonNew->Text = L"New Assembly Source";
				this->toolStripButtonNew->ToolTipText = L"Create New Assembly Source File";
				// 
				// toolStripButtonNewProject
				// 
				this->toolStripButtonNewProject->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->toolStripButtonNewProject->Enabled = false;
				this->toolStripButtonNewProject->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButtonNewProject.Image")));
				this->toolStripButtonNewProject->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->toolStripButtonNewProject->Name = L"toolStripButtonNewProject";
				this->toolStripButtonNewProject->Size = System::Drawing::Size(23, 22);
				this->toolStripButtonNewProject->Text = L"Create New Project";
				// 
				// toolStripButtonOpen
				// 
				this->toolStripButtonOpen->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->toolStripButtonOpen->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButtonOpen.Image")));
				this->toolStripButtonOpen->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->toolStripButtonOpen->Name = L"toolStripButtonOpen";
				this->toolStripButtonOpen->Size = System::Drawing::Size(23, 22);
				this->toolStripButtonOpen->Text = L"Open a single assembly source file";
				this->toolStripButtonOpen->Click += gcnew System::EventHandler(this, &Form_simUI::assemblySourceToolStripMenuItem_Click);
				// 
				// toolStripButtonOpenProject
				// 
				this->toolStripButtonOpenProject->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->toolStripButtonOpenProject->Enabled = false;
				this->toolStripButtonOpenProject->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButtonOpenProject.Image")));
				this->toolStripButtonOpenProject->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->toolStripButtonOpenProject->Name = L"toolStripButtonOpenProject";
				this->toolStripButtonOpenProject->Size = System::Drawing::Size(23, 22);
				this->toolStripButtonOpenProject->Text = L"Open a Project";
				// 
				// toolStripButtonSave
				// 
				this->toolStripButtonSave->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->toolStripButtonSave->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButtonSave.Image")));
				this->toolStripButtonSave->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->toolStripButtonSave->Name = L"toolStripButtonSave";
				this->toolStripButtonSave->Size = System::Drawing::Size(23, 22);
				this->toolStripButtonSave->Text = L"Save";
				// 
				// toolStripButtonSaveProject
				// 
				this->toolStripButtonSaveProject->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->toolStripButtonSaveProject->Enabled = false;
				this->toolStripButtonSaveProject->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButtonSaveProject.Image")));
				this->toolStripButtonSaveProject->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->toolStripButtonSaveProject->Name = L"toolStripButtonSaveProject";
				this->toolStripButtonSaveProject->Size = System::Drawing::Size(23, 22);
				this->toolStripButtonSaveProject->Text = L"Save Project";
				// 
				// toolStripSeparator3
				// 
				this->toolStripSeparator3->Name = L"toolStripSeparator3";
				this->toolStripSeparator3->Size = System::Drawing::Size(6, 25);
				// 
				// toolStripButtonCut
				// 
				this->toolStripButtonCut->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->toolStripButtonCut->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButtonCut.Image")));
				this->toolStripButtonCut->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->toolStripButtonCut->Name = L"toolStripButtonCut";
				this->toolStripButtonCut->Size = System::Drawing::Size(23, 22);
				this->toolStripButtonCut->Text = L"Cut";
				this->toolStripButtonCut->Click += gcnew System::EventHandler(this, &Form_simUI::cutToolStripMenuItem_Click);
				// 
				// toolStripButtonCopy
				// 
				this->toolStripButtonCopy->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->toolStripButtonCopy->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButtonCopy.Image")));
				this->toolStripButtonCopy->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->toolStripButtonCopy->Name = L"toolStripButtonCopy";
				this->toolStripButtonCopy->Size = System::Drawing::Size(23, 22);
				this->toolStripButtonCopy->Text = L"Copy";
				this->toolStripButtonCopy->Click += gcnew System::EventHandler(this, &Form_simUI::copyToolStripMenuItem_Click);
				// 
				// toolStripButtonPaste
				// 
				this->toolStripButtonPaste->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->toolStripButtonPaste->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButtonPaste.Image")));
				this->toolStripButtonPaste->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->toolStripButtonPaste->Name = L"toolStripButtonPaste";
				this->toolStripButtonPaste->Size = System::Drawing::Size(23, 22);
				this->toolStripButtonPaste->Text = L"Paste";
				this->toolStripButtonPaste->Click += gcnew System::EventHandler(this, &Form_simUI::pasteToolStripMenuItem_Click);
				// 
				// toolStripSeparator4
				// 
				this->toolStripSeparator4->Name = L"toolStripSeparator4";
				this->toolStripSeparator4->Size = System::Drawing::Size(6, 25);
				// 
				// toolStripButtonUndo
				// 
				this->toolStripButtonUndo->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->toolStripButtonUndo->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButtonUndo.Image")));
				this->toolStripButtonUndo->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->toolStripButtonUndo->Name = L"toolStripButtonUndo";
				this->toolStripButtonUndo->Size = System::Drawing::Size(23, 22);
				this->toolStripButtonUndo->Text = L"Undo";
				this->toolStripButtonUndo->Click += gcnew System::EventHandler(this, &Form_simUI::undoToolStripMenuItem_Click);
				// 
				// toolStripButtonRedo
				// 
				this->toolStripButtonRedo->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->toolStripButtonRedo->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButtonRedo.Image")));
				this->toolStripButtonRedo->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->toolStripButtonRedo->Name = L"toolStripButtonRedo";
				this->toolStripButtonRedo->Size = System::Drawing::Size(23, 22);
				this->toolStripButtonRedo->Text = L"Redo";
				this->toolStripButtonRedo->Click += gcnew System::EventHandler(this, &Form_simUI::redoToolStripMenuItem_Click);
				// 
				// splitContainerMain
				// 
				this->splitContainerMain->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
				this->splitContainerMain->Dock = System::Windows::Forms::DockStyle::Fill;
				this->splitContainerMain->Location = System::Drawing::Point(0, 74);
				this->splitContainerMain->Name = L"splitContainerMain";
				// 
				// splitContainerMain.Panel1
				// 
				this->splitContainerMain->Panel1->Controls->Add(this->tabControlSidepane);
				// 
				// splitContainerMain.Panel2
				// 
				this->splitContainerMain->Panel2->Controls->Add(this->splitContainerTextConsole);
				this->splitContainerMain->Size = System::Drawing::Size(993, 480);
				this->splitContainerMain->SplitterDistance = 143;
				this->splitContainerMain->TabIndex = 4;
				// 
				// tabControlSidepane
				// 
				this->tabControlSidepane->Controls->Add(this->tabPageProjectExp);
				this->tabControlSidepane->Controls->Add(this->tabPageRecFiles);
				this->tabControlSidepane->Dock = System::Windows::Forms::DockStyle::Fill;
				this->tabControlSidepane->Location = System::Drawing::Point(0, 0);
				this->tabControlSidepane->Name = L"tabControlSidepane";
				this->tabControlSidepane->SelectedIndex = 0;
				this->tabControlSidepane->Size = System::Drawing::Size(139, 476);
				this->tabControlSidepane->TabIndex = 0;
				// 
				// tabPageProjectExp
				// 
				this->tabPageProjectExp->Controls->Add(this->labelProjWarn);
				this->tabPageProjectExp->Location = System::Drawing::Point(4, 22);
				this->tabPageProjectExp->Name = L"tabPageProjectExp";
				this->tabPageProjectExp->Padding = System::Windows::Forms::Padding(3);
				this->tabPageProjectExp->Size = System::Drawing::Size(131, 450);
				this->tabPageProjectExp->TabIndex = 0;
				this->tabPageProjectExp->Text = L"Project Explorer";
				this->tabPageProjectExp->UseVisualStyleBackColor = true;
				// 
				// labelProjWarn
				// 
				this->labelProjWarn->AutoSize = true;
				this->labelProjWarn->Location = System::Drawing::Point(6, 8);
				this->labelProjWarn->Name = L"labelProjWarn";
				this->labelProjWarn->Size = System::Drawing::Size(177, 13);
				this->labelProjWarn->TabIndex = 0;
				this->labelProjWarn->Text = L"Projects are currently not supported.";
				// 
				// tabPageRecFiles
				// 
				this->tabPageRecFiles->Controls->Add(this->listViewRecentFiles);
				this->tabPageRecFiles->Location = System::Drawing::Point(4, 22);
				this->tabPageRecFiles->Name = L"tabPageRecFiles";
				this->tabPageRecFiles->Padding = System::Windows::Forms::Padding(3);
				this->tabPageRecFiles->Size = System::Drawing::Size(131, 450);
				this->tabPageRecFiles->TabIndex = 1;
				this->tabPageRecFiles->Text = L"Recent Files";
				this->tabPageRecFiles->UseVisualStyleBackColor = true;
				// 
				// listViewRecentFiles
				// 
				this->listViewRecentFiles->Dock = System::Windows::Forms::DockStyle::Fill;
				this->listViewRecentFiles->Location = System::Drawing::Point(3, 3);
				this->listViewRecentFiles->Name = L"listViewRecentFiles";
				this->listViewRecentFiles->Size = System::Drawing::Size(125, 444);
				this->listViewRecentFiles->TabIndex = 0;
				this->listViewRecentFiles->UseCompatibleStateImageBehavior = false;
				// 
				// splitContainerTextConsole
				// 
				this->splitContainerTextConsole->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
				this->splitContainerTextConsole->Dock = System::Windows::Forms::DockStyle::Fill;
				this->splitContainerTextConsole->Location = System::Drawing::Point(0, 0);
				this->splitContainerTextConsole->Name = L"splitContainerTextConsole";
				this->splitContainerTextConsole->Orientation = System::Windows::Forms::Orientation::Horizontal;
				// 
				// splitContainerTextConsole.Panel1
				// 
				this->splitContainerTextConsole->Panel1->Controls->Add(this->tabControlMain);
				// 
				// splitContainerTextConsole.Panel2
				// 
				this->splitContainerTextConsole->Panel2->Controls->Add(this->richTextBoxConsole);
				this->splitContainerTextConsole->Size = System::Drawing::Size(842, 476);
				this->splitContainerTextConsole->SplitterDistance = 343;
				this->splitContainerTextConsole->TabIndex = 0;
				// 
				// tabControlMain
				// 
				this->tabControlMain->Controls->Add(this->tabPageTextEdit);
				this->tabControlMain->Dock = System::Windows::Forms::DockStyle::Fill;
				this->tabControlMain->Location = System::Drawing::Point(0, 0);
				this->tabControlMain->Name = L"tabControlMain";
				this->tabControlMain->SelectedIndex = 0;
				this->tabControlMain->Size = System::Drawing::Size(840, 341);
				this->tabControlMain->TabIndex = 0;
				// 
				// tabPageTextEdit
				// 
				this->tabPageTextEdit->Controls->Add(this->richTextBoxTextEditor);
				this->tabPageTextEdit->Location = System::Drawing::Point(4, 22);
				this->tabPageTextEdit->Name = L"tabPageTextEdit";
				this->tabPageTextEdit->Padding = System::Windows::Forms::Padding(3);
				this->tabPageTextEdit->Size = System::Drawing::Size(832, 315);
				this->tabPageTextEdit->TabIndex = 0;
				this->tabPageTextEdit->Text = L"Text Editor";
				this->tabPageTextEdit->UseVisualStyleBackColor = true;
				// 
				// richTextBoxTextEditor
				// 
				this->richTextBoxTextEditor->AcceptsTab = true;
				this->richTextBoxTextEditor->ContextMenuStrip = this->contextMenuStripTextEditor;
				this->richTextBoxTextEditor->Dock = System::Windows::Forms::DockStyle::Fill;
				this->richTextBoxTextEditor->Font = (gcnew System::Drawing::Font(L"Courier New", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					static_cast<System::Byte>(0)));
				this->richTextBoxTextEditor->Location = System::Drawing::Point(3, 3);
				this->richTextBoxTextEditor->Name = L"richTextBoxTextEditor";
				this->richTextBoxTextEditor->Size = System::Drawing::Size(826, 309);
				this->richTextBoxTextEditor->TabIndex = 0;
				this->richTextBoxTextEditor->Text = L"";
				// 
				// contextMenuStripTextEditor
				// 
				this->contextMenuStripTextEditor->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->toolStripMenuItemCut, 
					this->toolStripMenuItemCopy, this->toolStripMenuItemPaste});
				this->contextMenuStripTextEditor->Name = L"contextMenuStripTextEditor";
				this->contextMenuStripTextEditor->Size = System::Drawing::Size(103, 70);
				// 
				// toolStripMenuItemCut
				// 
				this->toolStripMenuItemCut->Name = L"toolStripMenuItemCut";
				this->toolStripMenuItemCut->Size = System::Drawing::Size(102, 22);
				this->toolStripMenuItemCut->Text = L"Cut";
				this->toolStripMenuItemCut->Click += gcnew System::EventHandler(this, &Form_simUI::cutToolStripMenuItem_Click);
				// 
				// toolStripMenuItemCopy
				// 
				this->toolStripMenuItemCopy->Name = L"toolStripMenuItemCopy";
				this->toolStripMenuItemCopy->Size = System::Drawing::Size(102, 22);
				this->toolStripMenuItemCopy->Text = L"Copy";
				this->toolStripMenuItemCopy->Click += gcnew System::EventHandler(this, &Form_simUI::copyToolStripMenuItem_Click);
				// 
				// toolStripMenuItemPaste
				// 
				this->toolStripMenuItemPaste->Name = L"toolStripMenuItemPaste";
				this->toolStripMenuItemPaste->Size = System::Drawing::Size(102, 22);
				this->toolStripMenuItemPaste->Text = L"Paste";
				this->toolStripMenuItemPaste->Click += gcnew System::EventHandler(this, &Form_simUI::pasteToolStripMenuItem_Click);
				// 
				// richTextBoxConsole
				// 
				this->richTextBoxConsole->Dock = System::Windows::Forms::DockStyle::Fill;
				this->richTextBoxConsole->Font = (gcnew System::Drawing::Font(L"Courier New", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					static_cast<System::Byte>(0)));
				this->richTextBoxConsole->Location = System::Drawing::Point(0, 0);
				this->richTextBoxConsole->Name = L"richTextBoxConsole";
				this->richTextBoxConsole->ReadOnly = true;
				this->richTextBoxConsole->Size = System::Drawing::Size(840, 127);
				this->richTextBoxConsole->TabIndex = 0;
				this->richTextBoxConsole->Text = L"simUI Console\n---------------\n";
				// 
				// processSimulation
				// 
				this->processSimulation->StartInfo->Domain = L"";
				this->processSimulation->StartInfo->LoadUserProfile = false;
				this->processSimulation->StartInfo->Password = nullptr;
				this->processSimulation->StartInfo->StandardErrorEncoding = nullptr;
				this->processSimulation->StartInfo->StandardOutputEncoding = nullptr;
				this->processSimulation->StartInfo->UserName = L"";
				this->processSimulation->SynchronizingObject = this;
				this->processSimulation->OutputDataReceived += gcnew System::Diagnostics::DataReceivedEventHandler(this, &Form_simUI::processSimulation_OutputDataReceived);
				this->processSimulation->ErrorDataReceived += gcnew System::Diagnostics::DataReceivedEventHandler(this, &Form_simUI::processSimulation_ErrorDataReceived);
				this->processSimulation->Exited += gcnew System::EventHandler(this, &Form_simUI::processSimulation_Exited);
				// 
				// openFileDialogASMSource
				// 
				this->openFileDialogASMSource->FileName = L"openFileDialog";
				this->openFileDialogASMSource->Title = L"Open Assembly Source File...";
				// 
				// Form_simUI
				// 
				this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				this->ClientSize = System::Drawing::Size(993, 576);
				this->Controls->Add(this->splitContainerMain);
				this->Controls->Add(this->statusStripMain);
				this->Controls->Add(this->toolStripSimulation);
				this->Controls->Add(this->toolStripIO);
				this->Controls->Add(this->menuStrip_main);
				this->MainMenuStrip = this->menuStrip_main;
				this->Name = L"Form_simUI";
				this->Text = L"simUI";
				this->Load += gcnew System::EventHandler(this, &Form_simUI::Form_simUI_Load);
				this->menuStrip_main->ResumeLayout(false);
				this->menuStrip_main->PerformLayout();
				this->toolStripSimulation->ResumeLayout(false);
				this->toolStripSimulation->PerformLayout();
				this->toolStripIO->ResumeLayout(false);
				this->toolStripIO->PerformLayout();
				this->splitContainerMain->Panel1->ResumeLayout(false);
				this->splitContainerMain->Panel2->ResumeLayout(false);
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->splitContainerMain))->EndInit();
				this->splitContainerMain->ResumeLayout(false);
				this->tabControlSidepane->ResumeLayout(false);
				this->tabPageProjectExp->ResumeLayout(false);
				this->tabPageProjectExp->PerformLayout();
				this->tabPageRecFiles->ResumeLayout(false);
				this->splitContainerTextConsole->Panel1->ResumeLayout(false);
				this->splitContainerTextConsole->Panel2->ResumeLayout(false);
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->splitContainerTextConsole))->EndInit();
				this->splitContainerTextConsole->ResumeLayout(false);
				this->tabControlMain->ResumeLayout(false);
				this->tabPageTextEdit->ResumeLayout(false);
				this->contextMenuStripTextEditor->ResumeLayout(false);
				this->ResumeLayout(false);
				this->PerformLayout();

			}
#pragma endregion

			/// <summary>
			/// Clean up any resources being used.
			/// </summary>
			~Form_simUI()
			{
				try
				{
					if(!processSimulation->HasExited)
					{
							processSimulation->Kill();
					}
				}
				catch(...)
				{
					// everything is dying anyways, might as well just try to kill
				}

				if (components)
				{
					delete components;
				}
			}

			private: System::Void Form_simUI_Load(System::Object^  sender, System::EventArgs^  e)
			{

			}

			private: System::Void simulationToolbarToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
			{
				if(this->toolStripSimulation->Visible)
				{
					 this->toolStripSimulation->Visible = false;
					 this->simulationToolbarToolStripMenuItem->Checked = false;
				}
			
				else
				{
					this->toolStripSimulation->Visible = true;
					this->simulationToolbarToolStripMenuItem->Checked = true;
				}
			}

			private: System::Void iOBarToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
			{
				if(this->toolStripIO->Visible)
				{
					this->toolStripIO->Visible = false;
					this->iOBarToolStripMenuItem->Checked = false;
				}	
			 
				else
				{
					this->toolStripIO->Visible = true;
					this->iOBarToolStripMenuItem->Checked = true;
				}
			}

			private: System::Void aboutToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
			{
					Form_About^ about = gcnew Form_About();
					about->ShowDialog();
			}

			private: System::Void fontToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
			{
			 
			}

			private: System::Void toolStripButtonSimulate_Click(System::Object^  sender, System::EventArgs^  e)
			{
				if(richTextBoxTextEditor->Text == "")
				{
					this->richTextBoxConsole->Text += "Error: input file is empty.\n";
					return;
				}

				this->processSimulation = (gcnew System::Diagnostics::Process());
				reinitProc();
				this->toolStripButtonSimulate->Enabled = false;
				this->richTextBoxConsole->Text += "Starting new instance of MIPS Tools...\n";
				this->processSimulation->StartInfo->FileName = "mtshell.exe";
				this->processSimulation->StartInfo->UseShellExecute = false;
				this->processSimulation->StartInfo->CreateNoWindow = true;
				this->processSimulation->StartInfo->RedirectStandardError = true;
				this->processSimulation->StartInfo->RedirectStandardOutput = true;
				this->processSimulation->StartInfo->RedirectStandardInput = true;
				this->processSimulation->StartInfo->Arguments = "-WIN32_SHELL -c " + cpu_type + " -m " + mem_bits;
			 
				// Make sure to assign standard input and output correctly
				// Standard input: the current open file in the currently selected text file
				// Standard ouput: attach to the console

				try
				{
					this->processSimulation->Start();
					this->richTextBoxConsole->Text += "Simulation initiated.\n";
					this->toolStripButtonStop->Enabled = true;
				}

				catch(System::ComponentModel::Win32Exception^)
				{
					this->richTextBoxConsole->Text += ("MIPS Tools could not be started. Perhaps mtshell.exe is missing?\n");
					return;
				}

				// Reading
				processSimulation->BeginOutputReadLine();

				// Write program
				processSimulation->StandardInput->Write(richTextBoxTextEditor->Text);
				processSimulation->StandardInput->Flush();
				processSimulation->StandardInput->Close();
			}

			private: System::Void processSimulation_OutputDataReceived(System::Object^  sender, System::Diagnostics::DataReceivedEventArgs^  e)
			{
				this->richTextBoxConsole->Text += e->Data + "\n";
			}

			private: System::Void processSimulation_Exited(System::Object^  sender, System::EventArgs^  e)
			{
				this->richTextBoxConsole->Text += "Simulation has finished.\n";
				this->toolStripButtonSimulate->Enabled = true;
				this->toolStripButtonStop->Enabled = false;
			}

			private: System::Void toolStripButtonStop_Click(System::Object^  sender, System::EventArgs^  e)
			{
				if(!this->processSimulation->HasExited)
				{
					this->processSimulation->Kill();
				}
					
				this->richTextBoxConsole->Text += "Simulation has been aborted.\n";
				this->toolStripButtonSimulate->Enabled = true;
				this->toolStripButtonStop->Enabled = false;
			}

			private: System::Void processSimulation_ErrorDataReceived(System::Object^  sender, System::Diagnostics::DataReceivedEventArgs^  e)
			{
				this->richTextBoxConsole->Text += e->Data + "\n";
			}

			private: System::Void assemblySourceToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
			{
				if(openFileDialogASMSource->ShowDialog() != System::Windows::Forms::DialogResult::OK) return;

				try
				{
					System::IO::StreamReader^ reader = gcnew System::IO::StreamReader(openFileDialogASMSource->FileName);
					richTextBoxTextEditor->Text = reader->ReadToEnd();
				}
						 
				catch(System::IO::FileNotFoundException^)
				{
					this->richTextBoxConsole->Text += "Error: The file requested could not be opened and may not exist.\n";
				}
			}

			private: System::Void clearConsoleInputToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
			{
				this->richTextBoxConsole->Text = "";
			}

			private: System::Void consoleFontToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
			{
				fontDialogConsole->ShowDialog();
				this->richTextBoxConsole->Font = fontDialogConsole->Font;
			}

			private: System::Void textEditorFontToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
			{
				fontDialogTextEditor->ShowDialog();
				this->richTextBoxTextEditor->Font = fontDialogTextEditor->Font;
			}

			private: System::Void copyToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
			{
				this->richTextBoxTextEditor->Copy();
			}

			private: System::Void cutToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
			{
				this->richTextBoxTextEditor->Cut();
			}

			private: System::Void pasteToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
			{
				this->richTextBoxTextEditor->Paste();
			}

			private: System::Void exitToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
			{
				this->Close();
			}

			private: System::Void cPUTypeSelectionToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
			{
				cpusd->ShowDialog();
				cpu_type = cpusd->getCPUType();
			}

			private: System::Void memorySizeToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
			{
				memsd->ShowDialog();
				mem_bits = memsd->getMemoryBits();
			}

			private: System::Void undoToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
			{
				if(richTextBoxTextEditor->CanUndo)
					richTextBoxTextEditor->Undo();

			}

			private: System::Void redoToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
			{
				if(richTextBoxTextEditor->CanRedo)
					richTextBoxTextEditor->Redo();
			}
};
}
