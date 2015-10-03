#include "applicationui.hpp"

TextField *connector;
QString linkToOpen;

ApplicationUI::ApplicationUI(bb::cascades::Application *app) : QObject(app)
{
	//SHARE TAB CONTENTS

	shareManager = new NfcShareManager;

	/*locationPrompt = new SystemPrompt;
	locationPrompt->setTitle("Please enter your location");
	locationPrompt->confirmButton()->setLabel("Save");
	locationPrompt->setDefaultButton(locationPrompt->confirmButton());
	connect(locationPrompt, SIGNAL(finished(bb::system::SystemUiResult::Type)), this, SLOT(handleLocPrompt(bb::system::SystemUiResult::Type)));

	saveAction = ActionItem::create().
			enabled(FALSE).
			image("asset:///images/icons/ic_save_as.png").
			title("Save").
			connect(SIGNAL(triggered()), this, SLOT(openLocPrompt()));*/

	shareFB = CheckBox::create().
			checked(TRUE).
			connect(SIGNAL(checkedChanged(bool)), this, SLOT(setContentToShare()));

	TapHandler *fbTap = TapHandler::create().
			onTapped(this, SLOT(changeFB()));

	shareFBL = Label::create().
			text("Share my Facebook profile").
			addGestureHandler(fbTap).
			connect(SIGNAL(enabledChanged(bool)), this, SLOT(shareFBChanged(bool)));

	Container *shareFBC = Container::create().
			horizontal(HorizontalAlignment::Center).
			layout(StackLayout::create().orientation(LayoutOrientation::LeftToRight)).
			add(shareFB).
			add(shareFBL);

	shareLI = CheckBox::create().
			checked(TRUE).
			connect(SIGNAL(checkedChanged(bool)), this, SLOT(setContentToShare()));

	TapHandler *liTap = TapHandler::create().
			onTapped(this, SLOT(changeLI()));

	shareLIL = Label::create().
			text("Share my LinkedIn profile  ").
			addGestureHandler(liTap).
			connect(SIGNAL(enabledChanged(bool)), this, SLOT(shareLIChanged(bool)));

	Container *shareLIC = Container::create().
				horizontal(HorizontalAlignment::Center).
				layout(StackLayout::create().orientation(LayoutOrientation::LeftToRight)).
				add(shareLI).
				add(shareLIL);

	Container *shareChooser = Container::create().
			horizontal(HorizontalAlignment::Center).
			preferredWidth(600.0f).
			add(shareFBC).
			add(Divider::create()).
			add(shareLIC);

	Container *shareChooserRoot = Container::create().
			horizontal(HorizontalAlignment::Center).
			vertical(VerticalAlignment::Top).
			preferredWidth(768.0f).
			top(30.0f).
			//top(10.0f).
			bottom(30.0f).
			//bottom(10.0f).
			background(Color::Gray).
			add(shareChooser);


	TextStyle tapStyle;
	tapStyle.setFontWeight(FontWeight::W400);
	//tapStyle.setFontSize(FontSize::XLarge);
	tapStyle.setFontSize(FontSize::XXLarge);
	tapStyle.setTextAlign(TextAlign::Center);

	rNameLabel = Label::create().
			horizontal(HorizontalAlignment::Center).
			multiline(TRUE).
			textStyle(tapStyle);

	//TODO

	fbButton = ImageButton::create().
			defaultImage("asset:///images/fbLarge.png").
			pressedImage("asset:///images/fbLargePressed.png").
			//preferredSize(130.0f, 130.0f).
			preferredSize(192.0f, 192.0f).
			visible(FALSE).
			connect(SIGNAL(clicked()), this, SLOT(openFB()));

	liButton = ImageButton::create().
			defaultImage("asset:///images/liLarge.png").
			pressedImage("asset:///images/liLargePressed.png").
			//preferredSize(130.0f, 130.0f).
			preferredSize(192.0f, 192.0f).
			visible(FALSE).
			connect(SIGNAL(clicked()), this, SLOT(openLI()));

	Container *linksContainer = Container::create().
			layout(StackLayout::create().orientation(LayoutOrientation::LeftToRight)).
			horizontal(HorizontalAlignment::Center).
			add(fbButton).
			add(liButton);

	//TODO

	/*tapStyle.setFontSize(FontSize::PointValue);
	tapStyle.setFontSizeValue(10.5f);*/
	tapStyle.setFontSize(FontSize::XLarge);
	tapStyle.setFontWeight(FontWeight::W300);



	tapMessage = Label::create().
			horizontal(HorizontalAlignment::Center).
			multiline(TRUE).
			textStyle(tapStyle);

	//TODO

	Container *tapMessageC = Container::create().
			//preferredHeight(130.0f).
			preferredHeight(250.0f).
			add(tapMessage);

	//TODO

	Container *shareContent = Container::create().
			horizontal(HorizontalAlignment::Center).
			vertical(VerticalAlignment::Center).
			//vertical(VerticalAlignment::Bottom).
			add(tapMessageC).
			add(rNameLabel).
			add(linksContainer);

	Container *shareRoot = Container::create().
			layout(DockLayout::create()).
			add(shareChooserRoot).
			add(shareContent);

	sharePage = Page::create().
			content(shareRoot);


	//SAVED TAB CONTENTS

	MyItemClassFactory *myItemProvider = new MyItemClassFactory();

	deleteAction = DeleteActionItem::create().
			enabled(FALSE).
			connect(SIGNAL(triggered()), this, SLOT(deleteSelected()));

	clearListAction = ActionItem::create().
			enabled(FALSE).
			title("Clear list").
			image("asset:///images/icons/ic_clear_list.png").
			connect(SIGNAL(triggered()), this, SLOT(clearTheList()));

	nItemsSelected = 0;

	deletedToast = new SystemToast(app);
	deletedToast->button()->setLabel("Undo");
	deletedToast->setPosition(SystemUiPosition::BottomCenter);
	connect(deletedToast, SIGNAL(finished(bb::system::SystemUiResult::Type)), this, SLOT(handleToastFinish()));

	Label *emptyState = Label::create().
			horizontal(HorizontalAlignment::Center).
			multiline(TRUE).
			text("Save received profiles by tapping save and they will"
					" appear here").
					textStyle(tapStyle);

	emptyStateContainer = Container::create().
			layout(DockLayout::create()).
			horizontal(HorizontalAlignment::Center).
			vertical(VerticalAlignment::Center).
			add(emptyState);

	dataModel = new ArrayDataModel;
	tempList = new ArrayDataModel(app);

	QDir home = QDir::home();

	JsonDataAccess jda;
	QVariant list = jda.load(home.absoluteFilePath("savedForLater.json"));

	if(jda.hasError())
	{
		DataAccessError theError = jda.error();
		if(theError.errorType()==DataAccessErrorType::SourceNotFound)
		{
			qDebug()<<"Source not found";

			qDebug()<<QDir::homePath();
			QFile tempFile(home.absoluteFilePath("savedForLater.json"));
			tempFile.flush();

			if(tempFile.open(QIODevice::WriteOnly))
			{
				qDebug()<<"temp file opened";
			}
		}
	}
	else
	{
		dataModel->insert(0, list.value<QVariantList>());
	}

	listView = ListView::create().
			dataModel(dataModel).
			listItemProvider(myItemProvider).
			snapMode(SnapMode::LeadingEdge).
			connect(SIGNAL(triggered(const QVariantList)), this, SLOT(onListViewTriggered(const QVariantList)));

	savedRoot = Container::create().
			layout(DockLayout::create()).
			vertical(VerticalAlignment::Center).
			add(listView);

	if(dataModel->size()==0)
		savedRoot->replace(0, emptyStateContainer);
	else
		clearListAction->setEnabled(TRUE);


	savedPage = Page::create().
			content(savedRoot).
			addAction(clearListAction).
			addAction(deleteAction);

	//APPLICATION CONTENTS
	invokeManager = new InvokeManager;
	connect(invokeManager, SIGNAL(invoked(bb::system::InvokeRequest)), this, SLOT(onInvoked(const bb::system::InvokeRequest)));

	connector = TextField::create().
			parent(app).
			connect(SIGNAL(textChanged(QString)), this, SLOT(handleConnector(QString)));

	helpFirstTime = infoFirstTime = settingsFirstTime = TRUE;

	bbmToast = new SystemToast(app);
	bbmToast->setBody("BBM is not currently connected. Please setup/sign-in to BBM.");
	bbmToast->setIcon(QUrl("asset:///images/icons/ic_bbm.png"));

	appSheet = Sheet::create().
			peek(FALSE).
			parent(app);

	HelpActionItem *appHelp = HelpActionItem::create().
			connect(SIGNAL(triggered()), this, SLOT(displayHelp()));

	ActionItem *infoAction = ActionItem::create().
			image("asset:///images/icons/ic_info.png").
			title("Info").
			connect(SIGNAL(triggered()), this, SLOT(displayInfo()));

	ActionItem *shareBBM = ActionItem::create().
			image("asset:///images/icons/ic_bbm.png").
			title("Share App").
			connect(SIGNAL(triggered()), this, SLOT(shareApp()));

	SettingsActionItem *appSettings = SettingsActionItem::create().
			connect(SIGNAL(triggered()), this, SLOT(displaySettings()));

	Menu *appMenu = Menu::create().
			addAction(infoAction).
			addAction(shareBBM);
	appMenu->setHelpAction(appHelp);
	appMenu->setSettingsAction(appSettings);

	app->setMenu(appMenu);

	shareTab = Tab::create().
			title("Share Profiles").
			image("asset:///images/icons/ic_share.png");

	savedTab = Tab::create().
			title("Saved Profiles").
			image("asset:///images/icons/ic_view_list.png");

	tabChooser = TabbedPane::create().
			activePane(sharePage).
			showTabsOnActionBar(TRUE).
			add(shareTab).
			add(savedTab).
			connect(SIGNAL(activeTabChanged(bb::cascades::Tab*)), this, SLOT(handleTabChange(bb::cascades::Tab *)));

	app->setScene(tabChooser);

	appSavedSettings = new QSettings("STAW Creations", "ConnecTapp", app);
	if(appSavedSettings->value("firstTime", 1).toInt()==1)
	{
		appSavedSettings->setValue("firstTime", 0);
		displaySettings();
	}

	userName = appSavedSettings->value("userName", "").toString();
	userFbID = appSavedSettings->value("userFbID", "").toString();
	userLiID = appSavedSettings->value("userLiID", "").toString();
	//lastSavedLoc = appSavedSettings->value("lastSavedLoc", "").toString();

	if(userName!="")
	{
		rNameLabel->setText("Welcome\n"+ userName);
	}
	else
	{
		rNameLabel->setText("Welcome");
	}

	connect(app, SIGNAL(aboutToQuit()), this, SLOT(handleExit()));

	m_context = new bb::platform::bbm::Context(QUuid("b729199f-86e0-44ab-a819-677d8bdcb511"));
	if(m_context->registrationState() != bb::platform::bbm::RegistrationState::Allowed)
	{
		connect(m_context, SIGNAL(registrationStateUpdated (bb::platform::bbm::RegistrationState::Type)), this, SLOT(registrationStateUpdated (bb::platform::bbm::RegistrationState::Type)));
		m_context->requestRegisterApplication();
	}

	nfc_connect();
	//nfc_set_setting(NFC_SETTING_ENABLED_ASYNC, TRUE);
	nfc_set_setting(NFC_SETTING_ENABLED, TRUE);

	setContentToShare();
}

ApplicationUI::~ApplicationUI()
{
	qDebug()<<"DESTRUCTOR OPENED";

	delete invokeManager;

	delete shareManager;

	delete m_context;

	qDebug()<<"DESTRUCTOR CLOSED";
}

void ApplicationUI::changeFB()
{
	if(shareFB->isChecked())
		shareFB->setChecked(FALSE);
	else
		shareFB->setChecked(TRUE);
}

void ApplicationUI::changeLI()
{
	if(shareLI->isChecked())
		shareLI->setChecked(FALSE);
	else
		shareLI->setChecked(TRUE);
}

void ApplicationUI::clearTheList()
{
	listCleared = TRUE;
	tempList->clear();
	for(int i=0; i<dataModel->size(); i++)
	{
		tempList->append(dataModel->value(i));
	}

	dataModel->clear();
	nItemsSelected=0;
	clearListAction->setEnabled(FALSE);
	deleteAction->setEnabled(FALSE);

	savedRoot->replace(0, emptyStateContainer);

	deletedToast->setBody("List cleared");
	deletedToast->show();
}

void ApplicationUI::deleteSelected()
{
	delete [] tempPos;
	listCleared = FALSE;
	int tempIndex;
	tempList->clear();
	tempPos = new int[nItemsSelected];
	qDebug()<<"Reinitializing done";
	for(int i=0; i<nItemsSelected; i++)
	{
		tempIndex = listView->selected().first().toInt();
		tempPos[i]=tempIndex+i;
		tempList->append(dataModel->value(tempIndex));
		dataModel->removeAt(tempIndex);
	}
	nBackup = nItemsSelected;
	nItemsSelected=0;
	if(dataModel->size()==0)
	{
		savedRoot->replace(0, emptyStateContainer);
		clearListAction->setEnabled(FALSE);
	}
	deleteAction->setEnabled(FALSE);

	qDebug()<<"nBackup"<<nBackup;

	if(nBackup==1)
	{
		deletedToast->setBody("1 profile removed");
	}
	else
	{
		deletedToast->setBody(QString::number(nBackup) + " profiles removed");
	}
	deletedToast->show();
}

void ApplicationUI::displayHelp()
{
	if(helpFirstTime)
	{
		helpFirstTime = FALSE;


		//700x450

		//helpImage = ImageView::create().
		//		horizontal(HorizontalAlignment::Center);

		TextStyle textStyle;
		textStyle.setColor(Color::DarkMagenta);
		textStyle.setFontSize(FontSize::XLarge);
		textStyle.setFontWeight(FontWeight::W300);
		textStyle.setTextAlign(TextAlign::Center);
		textStyle.setLineHeight(0.9f);

		helpLabel = Label::create().
				vertical(VerticalAlignment::Top).
				horizontal(HorizontalAlignment::Center).
				multiline(TRUE).
				textStyle(textStyle);

		Container *textC = Container::create().
				layout(DockLayout::create()).
				horizontal(HorizontalAlignment::Center).
				preferredHeight(450.0f).
				add(helpLabel);

		helpSlider = Slider::create().
				horizontal(HorizontalAlignment::Center).
				preferredWidth(700.0f);
		helpSlider->setRange(0.0f, 4.0f);
		connect(helpSlider, SIGNAL(valueChanged(float)), this, SLOT(handleHelpSlider(float)));
		connect(helpSlider, SIGNAL(immediateValueChanged(float)), this, SLOT(handleHelpSliderImm(float)));

		Container *helpSliderC = Container::create().
				horizontal(HorizontalAlignment::Center).
				vertical(VerticalAlignment::Bottom).
				bottom(50.0f).
				add(helpSlider);

		Container *content = Container::create().
				vertical(VerticalAlignment::Center).
				horizontal(HorizontalAlignment::Center).
				//add(helpImage).
				add(textC);

		Container *root = Container::create().
				layout(DockLayout::create()).
				add(content).
				add(helpSliderC);

		ActionItem *close = ActionItem::create().
				title("Close").
				connect(SIGNAL(triggered()), appSheet, SLOT(close()));

		TitleBar *titleBar = TitleBar::create().
				title("Help").
				dismissAction(close);

		helpPage = Page::create().
				content(root).
				titleBar(titleBar);
	}
	helpLevel=0;
	helpSlider->setValue(0.0f);
	setContentForHelp();

	appSheet->setContent(helpPage);
	appSheet->open();
}

void ApplicationUI::displayInfo()
{
	if(infoFirstTime)
	{
		infoFirstTime = FALSE;

		ImageButton *infoLogo = ImageButton::create().
				horizontal(HorizontalAlignment::Center).
				defaultImage("asset:///images/logos/logo.png").
				pressedImage("asset:///images/logos/logoPressed.png").
				connect(SIGNAL(clicked()), this, SLOT(goToAppPage()));

		TextStyle textStyle;
		textStyle.setFontWeight(FontWeight::W300);
		textStyle.setFontSize(FontSize::XLarge);
		textStyle.setTextAlign(TextAlign::Center);

		Label *infoLabel = Label::create().multiline(TRUE).
				horizontal(HorizontalAlignment::Center).
				textStyle(textStyle).
				text("built by STAW\n"
						"with help from\n"
						"Rubus Labs\n"
						"and\n"
						"Startup Village, Kochi");

		ImageButton *svLogo = ImageButton::create().
				defaultImage("asset:///images/logos/sv.png").
				pressedImage("asset:///images/logos/svPressed.png").
				connect(SIGNAL(clicked()), this, SLOT(goToSV()));;

		ImageButton *rubusLogo = ImageButton::create().
				defaultImage("asset:///images/logos/rubus.png").
				pressedImage("asset:///images/logos/rubusPressed.png").
				connect(SIGNAL(clicked()), this, SLOT(goToRubus()));;

		Container *svAndRubus = Container::create().
				layout(StackLayout::create().orientation(LayoutOrientation::LeftToRight)).
				horizontal(HorizontalAlignment::Center).
				add(svLogo).
				add(rubusLogo);

		textStyle.setFontSize(FontSize::Medium);
		textStyle.setColor(Color::Blue);

		TapHandler *ppHandler = TapHandler::create().
				onTapped(this, SLOT(goToPrivacyPolicy()));

		Label *privacyPolicy = Label::create().
				vertical(VerticalAlignment::Bottom).
				horizontal(HorizontalAlignment::Center).
				textStyle(textStyle).
				text("View privacy policy").
				addGestureHandler(ppHandler);

		Container *content = Container::create().
				vertical(VerticalAlignment::Center).
				horizontal(HorizontalAlignment::Center).
				add(infoLogo).
				add(infoLabel).
				add(svAndRubus).
				add(privacyPolicy);

		Container *root = Container::create().
				layout(DockLayout::create()).
				add(content);

		ActionItem *close = ActionItem::create().
				title("Close").
				connect(SIGNAL(triggered()), appSheet, SLOT(close()));

		TitleBar *titleBar = TitleBar::create().
				title("Info").
				dismissAction(close);

		infoPage = Page::create().
				content(root).
				titleBar(titleBar);
	}
	appSheet->setContent(infoPage);
	appSheet->open();
}

void ApplicationUI::displaySettings()
{
	if(settingsFirstTime)
	{
		settingsFirstTime = FALSE;

		Divider div1, div2;

		TextStyle getIDStyle;
		getIDStyle.setFontSize(FontSize::XLarge);
		getIDStyle.setFontWeight(FontWeight::W300);
		//getIDStyle.setColor(Color::Blue);

		Label *description = Label::create().
				text("Please enter your details: ").
				textStyle(getIDStyle);
		/*
		TextStyle descStyle;
		descStyle.setColor(Color::White);

		Container *nameContainer = Container::create().
				background(Color::Black).
				preferredWidth(768.0f).
				add(Label::create().text("Name:").textStyle(descStyle));
		 */
		nameField = TextField::create().
				hintText("Enter your name");

		getIDStyle.setFontSize(FontSize::Small);
		getIDStyle.setFontWeight(FontWeight::W200);
		getIDStyle.setColor(Color::Blue);

		TapHandler *fbTapHandler = TapHandler::create().
				onTapped(this, SLOT(getFbID()));

		Label *getFB = Label::create().
				text("Tap here to get your Facebook ID").
				textStyle(getIDStyle).
				addGestureHandler(fbTapHandler);

		fbField = TextField::create().
				hintText("Enter your Facebook ID");

		TapHandler *liTapHandler = TapHandler::create().
				onTapped(this, SLOT(getLiID()));

		Label *getLI = Label::create().
				text("Tap here to get your LinkedIn ID").
				textStyle(getIDStyle).
				addGestureHandler(liTapHandler);

		liField = TextField::create().
				hintText("Enter your LinkedIn ID");

		Container *content = Container::create().
				vertical(VerticalAlignment::Center).
				horizontal(HorizontalAlignment::Center).
				right(20.0f).
				left(20.0f).
				add(description).
				//add(nameContainer).
				add(nameField).
				add(&div1).
				add(fbField).
				add(getFB).
				add(&div2).
				add(liField).
				add(getLI);

		Container *root = Container::create().
				layout(DockLayout::create()).
				add(content);

		ActionItem *cancel = ActionItem::create().
				title("Cancel").
				connect(SIGNAL(triggered()), appSheet, SLOT(close()));

		ActionItem *saveSettings = ActionItem::create().
				title("Save").
				connect(SIGNAL(triggered()), this, SLOT(submitted()));

		TitleBar *titleBar = TitleBar::create().
				title("Settings").
				dismissAction(cancel).
				acceptAction(saveSettings);

		settingsPage = Page::create().
				content(root).
				titleBar(titleBar);
	}

	nameField->setText(userName);
	fbField->setText(userFbID);
	liField->setText(userLiID);

	appSheet->setContent(settingsPage);
	appSheet->open();
}

void ApplicationUI::getFbID()
{
	InvokeRequest invokeRequest;
	invokeRequest.setTarget("sys.browser");
	invokeRequest.setAction("bb.action.OPEN");
	invokeRequest.setMimeType("text/html");
	invokeRequest.setUri("http://connectapp.3owl.com/");

	invokeManager->invoke(invokeRequest);
}

void ApplicationUI::getLiID()
{
	InvokeRequest invokeRequest;
	invokeRequest.setTarget("sys.browser");
	invokeRequest.setAction("bb.action.OPEN");
	invokeRequest.setMimeType("text/html");
	invokeRequest.setUri("http://connectapp.3owl.com/lihomepage.html");

	invokeManager->invoke(invokeRequest);
}

void ApplicationUI::goToAppPage()
{
	InvokeRequest invokeRequest;
	invokeRequest.setTarget("sys.browser");
	invokeRequest.setAction("bb.action.OPEN");
	invokeRequest.setMimeType("text/html");
	invokeRequest.setUri("http://m.facebook.com/connectappbystaw");

	invokeManager->invoke(invokeRequest);
}

void ApplicationUI::goToPrivacyPolicy()
{
	InvokeRequest invokeRequest;
	invokeRequest.setTarget("sys.browser");
	invokeRequest.setAction("bb.action.OPEN");
	invokeRequest.setMimeType("text/html");
	invokeRequest.setUri("http://www.aassk.in/staw/privacypolicy.html");

	invokeManager->invoke(invokeRequest);
}

void ApplicationUI::goToRubus()
{
	InvokeRequest invokeRequest;
	invokeRequest.setTarget("sys.browser");
	invokeRequest.setAction("bb.action.OPEN");
	invokeRequest.setMimeType("text/html");
	invokeRequest.setUri("http://startupvillage.in/rubuslabs");

	invokeManager->invoke(invokeRequest);
}

void ApplicationUI::goToSV()
{
	InvokeRequest invokeRequest;
	invokeRequest.setTarget("sys.browser");
	invokeRequest.setAction("bb.action.OPEN");
	invokeRequest.setMimeType("text/html");
	invokeRequest.setUri("http://startupvillage.in");

	invokeManager->invoke(invokeRequest);
}

void ApplicationUI::handleConnector(QString text)
{
	if(text=="FB")
	{
		InvokeRequest invokeRequest;
		invokeRequest.setTarget("sys.browser");
		invokeRequest.setAction("bb.action.OPEN");
		invokeRequest.setMimeType("text/html");
		invokeRequest.setUri("http://m.facebook.com/" + linkToOpen);

		invokeManager->invoke(invokeRequest);
	}
	else if(text=="LI")
	{
		InvokeRequest invokeRequest;
		invokeRequest.setTarget("sys.browser");
		invokeRequest.setAction("bb.action.OPEN");
		invokeRequest.setMimeType("text/html");
		invokeRequest.setUri(linkToOpen);

		invokeManager->invoke(invokeRequest);
	}
	connector->setText("");
}

void ApplicationUI::handleExit()
{
	qDebug()<<"Exiting.....";

	QMap<QString,QVariant> map;
	QVariant data;

	QList<QVariant> list;

	for(int i=0; i<dataModel->size(); i++)
	{
		map = dataModel->value(i).toMap();
		//qDebug()<<map["name"].toString();
		list<<map;
	}

	data = QVariant(list);

	QDir home = QDir::home();
	QFile tempFile(home.absoluteFilePath("savedForLater.json"));

	if(tempFile.open(QIODevice::WriteOnly))
	{
		JsonDataAccess jda;
		jda.save(data, &tempFile);
	}

	appSavedSettings->setValue("userName", userName);
	appSavedSettings->setValue("userFbID", userFbID);
	appSavedSettings->setValue("userLiID", userLiID);
	//appSavedSettings->setValue("lastSavedLoc", lastSavedLoc);
	appSavedSettings->sync();
}

void ApplicationUI::handleHelpSlider(float val)
{
	if(val<=0.75)
	{
		helpSlider->setValue(0.0);
	}
	else if(val>=0.75 && val<=1.75)
	{
		helpSlider->setValue(1.0);
	}
	else if(val>=1.75 && val<=2.75)
	{
		helpSlider->setValue(2.0);
	}
	else if(val>=2.75 && val<3.75)
	{
		helpSlider->setValue(3.0);
	}
	else if(val>=3.75)
	{
		helpSlider->setValue(4.0);
	}
	/*else if(val>=3.75 && val<=4.75)
	{
		helpSlider->setValue(4.0);
	}
	else if(val>=4.75 && val<=5.75)
	{
		helpSlider->setValue(5.0);
	}
	else if(val>=5.75)
	{
		helpSlider->setValue(6.0);
	}*/
}

void ApplicationUI::handleHelpSliderImm(float val)
{
	if(val<=0.75)
	{
		helpLevel=0;
	}
	else if(val>=0.75 && val<=1.75)
	{
		helpLevel=1;
	}
	else if(val>=1.75 && val<=2.75)
	{
		helpLevel=2;
	}
	else if(val>=2.75 && val<=3.75)
	{
		helpLevel=3;
	}
	else if(val>=3.75)
	{
		helpLevel=4;
	}
	/*else if(val>=3.75 && val<=4.75)
	{
		helpLevel=4;
	}
	else if(val>=4.75 && val<=5.75)
	{
		helpLevel=5;
	}
	else if(val>5.75)
	{
		helpLevel=6;
	}*/
	setContentForHelp();
}

/*void ApplicationUI::handleLocPrompt(bb::system::SystemUiResult::Type result)
{
	if(result==SystemUiResult::ConfirmButtonSelection)
	{
		//lastSavedLoc = locationPrompt->inputFieldTextEntry();

		QVariantMap map;

		map["name"] = rName;
		map["metPlace"] = lastSavedLoc;
		map["rfbID"] = rfbID;
		map["rliID"] = rliID;
		dataModel->append(map);
		clearListAction->setEnabled(TRUE);

		saveAction->setEnabled(FALSE);
		saveAction->setTitle("Done");
		saveAction->setImage("asset:///images/icons/ic_done.png");

		if(savedRoot->at(0)!=listView)
			savedRoot->replace(0, listView);
	}
}*/

void ApplicationUI::handleTabChange(bb::cascades::Tab *selectedTab)
{
	if(selectedTab==shareTab)
	{
		tabChooser->setActivePane(sharePage);
	}
	else
	{
		tabChooser->setActivePane(savedPage);
	}
}

void ApplicationUI::handleToastFinish()
{
	if(deletedToast->buttonSelection()==deletedToast->button())
	{
		if(listCleared)
		{
			for(int i=0; i<tempList->size(); i++)
			{
				dataModel->append(tempList->value(i));
			}
		}
		else
		{
			for(int i=0; i<nBackup; i++)
			{
				qDebug()<<"inserted into: "<<*(tempPos+i)<<"in datamodel ";
				dataModel->insert(*(tempPos+i), tempList->value(i));
				qDebug()<<"Done "<<i+1<<"times";
			}
		}
		clearListAction->setEnabled(TRUE);

		if(savedRoot->at(0)!=listView)
			savedRoot->replace(0, listView);

		qDebug()<<"UNDELETED";
	}
}

void ApplicationUI::onInvoked(const bb::system::InvokeRequest &request)
{
	//QVariantMap map = request.metadata();

	int tempCount;

	QString temp = request.data();
	qDebug()<<temp;

	temp = temp.right(temp.size()-4);

	if(temp.at(0)=='$')
	{
		rNameLabel->setText("No name received");
		rName = "";
		temp = temp.right(temp.size()-3);
	}
	else
	{
		tempCount = temp.indexOf("FB");

		rName = temp.left(tempCount);
		qDebug()<<"NAME: "<<rName;

		temp = temp.right(temp.size()-tempCount-2);
	}
	qDebug()<<"AFTER NAME DELETE: "<<temp;
	rNameLabel->setText(rName);

	if(temp.at(0)=='$')
	{
		rfbID = "";
		fbButton->setVisible(FALSE);

		temp = temp.right(temp.size()-3);
	}
	else
	{
		tempCount = temp.indexOf("LI");

		rfbID = temp.left(tempCount);
		fbButton->setVisible(TRUE);

		temp = temp.right(temp.size()-tempCount-2);
	}
	qDebug()<<"AFTER FB DELETE: "<<temp;

	if(temp.at(0)=='$')
	{
		rliID = "";
		liButton->setVisible(FALSE);
	}
	else
	{
		rliID = temp;
		liButton->setVisible(TRUE);
	}

	qDebug()<<rName<<"  "<<rfbID<<"  "<<rliID;

	if(!(rfbID!="" || rliID!="" || rName!=""))
	{
		rNameLabel->setText("No data received");
	}
	else
	{
		QVariantMap map;

		map["name"] = rName;
		map["rfbID"] = rfbID;
		map["rliID"] = rliID;
		dataModel->append(map);
		clearListAction->setEnabled(TRUE);

		if(savedRoot->at(0)!=listView)
			savedRoot->replace(0, listView);
	}

	//if(tabChooser->activeTab()!=shareTab)
		//tabChooser->setActiveTab(shareTab);
}

void ApplicationUI::onListViewTriggered(const QVariantList indexPath)
{
	if(listView->isSelected(indexPath))
	{
		listView->select(indexPath, FALSE);
		if(--nItemsSelected==0)
		{
			deleteAction->setEnabled(FALSE);
		}
	}
	else
	{
		listView->select(indexPath, TRUE);
		nItemsSelected++;
		deleteAction->setEnabled(TRUE);
	}
}

void ApplicationUI::openFB()
{
	InvokeRequest invokeRequest;
	invokeRequest.setTarget("sys.browser");
	invokeRequest.setAction("bb.action.OPEN");
	invokeRequest.setMimeType("text/html");
	invokeRequest.setUri("http://m.facebook.com/" + rfbID);

	invokeManager->invoke(invokeRequest);
}

void ApplicationUI::openLI()
{
	InvokeRequest invokeRequest;
	invokeRequest.setTarget("sys.browser");
	invokeRequest.setAction("bb.action.OPEN");
	invokeRequest.setMimeType("text/html");
	invokeRequest.setUri(rliID);

	invokeManager->invoke(invokeRequest);
}

/*void ApplicationUI::openLocPrompt()
{
	locationPrompt->inputField()->setDefaultText(lastSavedLoc);
	locationPrompt->show();
}*/

void ApplicationUI::registrationStateUpdated(bb::platform::bbm::RegistrationState::Type state)
{
	if(state==bb::platform::bbm::RegistrationState::Allowed)
	{
		m_messageService = new bb::platform::bbm::MessageService(m_context, this);
		m_userProfile = new bb::platform::bbm::UserProfile(m_context, this);
	}
	else if(state == bb::platform::bbm::RegistrationState::Unregistered)
	{
		m_context->requestRegisterApplication();
	}
}

void ApplicationUI::setContentToShare()
{
	if(userFbID=="" && userLiID=="") //NONE ARE PRESENT
	{
		shareFBL->setEnabled(FALSE);
		shareFB->setEnabled(FALSE);
		shareFB->setChecked(FALSE);

		shareLIL->setEnabled(FALSE);
		shareLI->setEnabled(FALSE);
		shareLI->setChecked(FALSE);

		tapMessage->setText("To share your profiles, please add them in settings");
	}
	else if(userFbID!="")
	{
		if(userLiID=="") //ONLY FB IS PRESENT
		{
			shareLIL->setEnabled(FALSE);
			shareLI->setEnabled(FALSE);
			shareLI->setChecked(FALSE);

			if(shareFB->isChecked())
				tapMessage->setText("Now tap your phones to share your Facebook profile. Add your LinkedIn "
						"profile to share it");
			else
				tapMessage->setText("Please choose a profile to share");

		}
		else //BOTH ARE PRESENT
		{
			if(shareFB->isChecked() && shareLI->isChecked())
				tapMessage->setText("Now tap your phones to share your Facebook and LinkedIn profiles");
			else if(shareFB->isChecked())
				tapMessage->setText("Now tap your phones to share your Facebook profile");
			else if(shareLI->isChecked())
				tapMessage->setText("Now tap your phones to share your LinkedIn profile");
			else
				tapMessage->setText("Please choose a profile to share");
		}
	}
	else //ONLY LI IS PRESENT
	{
		shareFBL->setEnabled(FALSE);
		shareFB->setEnabled(FALSE);
		shareFB->setChecked(FALSE);

		if(shareLI->isChecked())
			tapMessage->setText("Now tap your phones to share your LinkedIn profile. Add your Facebook "
					"profile to share it");
		else
			tapMessage->setText("Please choose a profile to share");
	}

	QString temp;
	if(userName=="")
		temp.append("$");
	else
		temp.append(userName);

	temp.append("FB");

	if(userFbID=="" || !shareFB->isChecked())
		temp.append("$");
	else
		temp.append(userFbID);

	temp.append("LI");

	if(userLiID=="" || !shareLI->isChecked())
		temp.append("$");
	else
		temp.append(userLiID);

	NfcShareDataContent contentToShare;
	contentToShare.setData(temp.toUtf8());
	contentToShare.setMimeType("staw/connecTapp");
	qDebug()<<"DATA:"<<contentToShare.data();

	//shareManager->setShareMode(NfcShareMode::DataSnep);
	shareManager->setShareMode(NfcShareMode::Data);
	shareManager->setShareContent(contentToShare);
}

void ApplicationUI::setContentForHelp()
{
	switch(helpLevel)
	{
	case 0:
		//helpImage->setImage(Image("asset:///images/helpPage/0.png"));
		helpLabel->setText("ConnecTapp helps you connect to the "
				"people you meet. With a tap of your phones, you can share "
				"your Facebook and LinkedIn profiles and instanly share your profiles.");
		break;

	case 1:
		//helpImage->setImage("asset:///images/helpPage/1.png");
		helpLabel->setText("In order to share profiles, the respective profiles need "
				"to be associated with the app. "
				"Also, NFC needs to be turned on and the app automatically requests "
				"to turn it on at startup.");
		break;

	case 2:
		//helpImage->setImage("asset:///images/helpPage/2.png");
		helpLabel->setText("To associate your profiles with the app, "
				"enter the profile IDs of respective accounts in settings. This needs to "
				"be done only once.");
		break;

	case 3:
		//helpImage->setImage("asset:///images/helpPage/3.png");
		helpLabel->setText("In order to exchange profile details, the app "
				"needs to be installed and open on both the devices. Then simply tap "
				"the backs of your phones and it's done.");
		break;

	case 4:
		//helpImage->setImage("asset:///images/helpPage/4.png");
		helpLabel->setText("After profiles are received, they will be automatically "
				"saved for future reference. You can check this list any time to connect to them.");
		break;
/*
	case 5:
		//helpImage->setImage("asset:///images/helpPage/5.png");
		helpLabel->setText("A timer keeps track of the time in MM:SS since you "
				"started the current game. A flag counter shows you the number "
				"of squares left to be flagged. A pause button is also provided.");
		break;

	case 6:
		//helpImage->setImage("asset:///images/helpPage/6.png");
		helpLabel->setText("The easy and medium levels are designed to help you "
				"get acquainted with the game and the hard level to test the real "
				"puzzle solver in you. Good luck.");
		break;*/
	default:
		qDebug()<<"Unexpected value for helpLevel: "<<helpLevel;
		break;
	}
}

void ApplicationUI::shareApp()
{
	if(m_context->registrationState() == bb::platform::bbm::RegistrationState::Allowed)
	{
		m_messageService->sendDownloadInvitation();
	}
	else
	{
		bbmToast->show();
		m_context->requestRegisterApplication();
	}
}

void ApplicationUI::shareFBChanged(bool enabled)
{
	if(!enabled)
		shareFBL->textStyle()->setColor(Color::LightGray);
	else
		shareFBL->textStyle()->resetColor();
}

void ApplicationUI::shareLIChanged(bool enabled)
{
	if(!enabled)
		shareLIL->textStyle()->setColor(Color::LightGray);
	else
		shareLIL->textStyle()->resetColor();
}

void ApplicationUI::submitted()
{
	QString backupFB, backupLI;

	backupFB = userFbID;
	backupLI = userLiID;

	//saveSettings->setEnabled(FALSE);
	userName = nameField->text();
	userFbID = fbField->text();
	userLiID = liField->text();

	if(userFbID!=backupFB && backupFB=="")
	{
		shareFBL->setEnabled(TRUE);
		shareFB->setEnabled(TRUE);
		shareFB->setChecked(TRUE);
	}

	if(userLiID!=backupLI && backupLI=="")
	{
		shareLIL->setEnabled(TRUE);
		shareLI->setEnabled(TRUE);
		shareLI->setChecked(TRUE);
	}

	if(userName!="" && rNameLabel->text().contains("Welcome"))
	{
		rNameLabel->setText("Welcome\n"+ userName);
	}

	//appSavedSettings->setValue("userName", userName);
	//appSavedSettings->setValue("userFbID", userFbID);
	//appSavedSettings->setValue("userLiID", userLiID);

	appSheet->close();

	setContentToShare();
}

//////////////////////////////////////////////////////////////////////

MyItemClass::MyItemClass(Container *parent) :
        																CustomControl(parent)
{
	// A Colored Container will be used to show if an item is highlighted.
	mHighlighContainer = Container::create().
			horizontal(HorizontalAlignment::Center).
			vertical(VerticalAlignment::Center).
			background(Color::fromARGB(0xff00A8DF)).
			opacity(0.0).
			preferredWidth(760.0f).
			preferredHeight(108.0f);

	// A list item label, docked to the center, the text is set in updateItem.
	nameLabel = Label::create().
			text(" ").
			vertical(VerticalAlignment::Center).
			horizontal(HorizontalAlignment::Left);//.
			//textStyle(SystemDefaults::TextStyles::titleText());
	nameLabel->textStyle()->setFontSize(FontSize::XLarge);
	nameLabel->textStyle()->setFontWeight(FontWeight::W300);
/*
	metPlaceLabel = Label::create().
			text(" ").
			vertical(VerticalAlignment::Bottom).
			horizontal(HorizontalAlignment::Left).
			textStyle(SystemDefaults::TextStyles::subtitleText());
*/
	Container *textContainer = Container::create().
			layout(DockLayout::create()).
			horizontal(HorizontalAlignment::Left).
			vertical(VerticalAlignment::Center).
			preferredHeight(100.0f).
			add(nameLabel);//.
			//add(metPlaceLabel);


	// The list item image, docked to the top, the actual image is set in updateItem.
	fbImage = ImageButton::create().
			horizontal(HorizontalAlignment::Right).
			vertical(VerticalAlignment::Center).
			preferredSize(100.0f, 100.0f).
			connect(SIGNAL(clicked()), this, SLOT(connectToFB()));

	liImage = ImageButton::create().
			horizontal(HorizontalAlignment::Right).
			vertical(VerticalAlignment::Center).
			preferredSize(100.0f, 100.0f).
			connect(SIGNAL(clicked()), this, SLOT(connectToLI()));

	Container *imageContainer = Container::create().
			layout(StackLayout::create().orientation(LayoutOrientation::LeftToRight)).
			horizontal(HorizontalAlignment::Right).
			vertical(VerticalAlignment::Center).
			add(fbImage).
			add(liImage);

	// Content Container, Image + text with padding to get alignment on background image.
	Container *contentContainer = Container::create().
			layout(DockLayout::create()).
			horizontal(HorizontalAlignment::Center).
			vertical(VerticalAlignment::Center).
			preferredWidth(750.0f).
			preferredHeight(108.0f).
			add(textContainer).
			add(imageContainer);


	Divider *myDivider = Divider::create().
			horizontal(HorizontalAlignment::Center).
			vertical(VerticalAlignment::Bottom);

	// Dock layout with margins inside.
	Container *itemContainer = Container::create().
			layout(DockLayout::create()).
			left(15.0f).
			right(15.0f).
			add(mHighlighContainer).
			add(contentContainer).
			add(myDivider);

	setRoot(itemContainer);
}

MyItemClass::~MyItemClass()
{
	/*delete fbImage;
	delete liImage;
	delete nameLabel;
	delete metPlaceLabel;
	delete mHighlighContainer;
	//delete borderContainer;
	delete itemContainer;*/
	//delete fillContainer;
}

void MyItemClass::connectToFB()
{
	linkToOpen = fbID;
	connector->setText("FB");
	qDebug()<<fbID;
}

void MyItemClass::connectToLI()
{
	linkToOpen = liID;
	connector->setText("LI");
	qDebug()<<liID;
}

void MyItemClass::activate(bool activate)
{
	// There is no special activate state, select and activated looks the same.
	/*if(activate)
	{
		borderContainer->setVisible(TRUE);
	}
	else
	{
		borderContainer->setVisible(FALSE);
	}*/
	select(activate);
}

void MyItemClass::reset(bool selected, bool activated)
{
	Q_UNUSED(activated);

	// Since items are recycled the reset function is where we have
	// to make sure that item state, defined by the arguments, is correct.
	select(selected);
}

void MyItemClass::select(bool select)
{
	// When an item is selected show the colored highlight Container
	if(select) {
		mHighlighContainer->setOpacity(0.4f);
	} else {
		mHighlighContainer->setOpacity(0.0f);
	}
}

void MyItemClass::updateItem(const QString text, const QString fb, const QString li)
{
	// Update image and text for the current item.
	//metPlaceLabel->setText(metText);
	nameLabel->setText(text);
	if(fb!="")
	{
		fbImage->setEnabled(TRUE);
		fbImage->setDefaultImage("asset:///images/fb.png");
		fbImage->setPressedImage("asset:///images/fbPressed.png");
		fbID = fb;
	}
	else
		fbImage->setEnabled(FALSE);

	if(li!="")
	{
		liImage->setEnabled(TRUE);
		liImage->setDefaultImage("asset:///images/li.png");
		liImage->setPressedImage("asset:///images/liPressed.png");
		liID = li;
	}
	else
		liImage->setEnabled(FALSE);
}


MyItemClassFactory::MyItemClassFactory()
{
}

VisualNode * MyItemClassFactory::createItem(ListView*/* list*/, const QString &/*type*/)
{
	//We only have one item type so we do not need to check the type variable.
	MyItemClass *myItem = new MyItemClass();
	return myItem;
}

void MyItemClassFactory::updateItem(ListView* list, bb::cascades::VisualNode *listItem,
		const QString &type, const QVariantList &indexPath, const QVariant &data)
{
	Q_UNUSED(list);
	Q_UNUSED(type);
	Q_UNUSED(indexPath);

	// Update the control with correct data.
	QVariantMap map = data.value<QVariantMap>();
	MyItemClass *myItem = static_cast<MyItemClass *>(listItem);
	// Call  the instance of our CustomContrlol MyItemClass and provide the data we want it to layout
	myItem->updateItem(map["name"].toString(), map["rfbID"].toString(), map["rliID"].toString());
}
