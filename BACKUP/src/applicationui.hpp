#ifndef ApplicationUI_HPP_
#define ApplicationUI_HPP_

#include <QObject>
#include <QSettings>
#include <nfc/nfc.h>
#include <bb/cascades/ActionItem>
#include <bb/cascades/Application>
#include <bb/cascades/ArrayDataModel>
//#include <bb/cascades/Button>
#include <bb/cascades/CheckBox>
#include <bb/cascades/Container>
#include <bb/cascades/CustomControl>
#include <bb/cascades/DeleteActionItem>
#include <bb/cascades/DockLayout>
#include <bb/cascades/Divider>
#include <bb/cascades/HelpActionItem>
#include <bb/cascades/ImageButton>
#include <bb/cascades/ImageView>
#include <bb/system/InvokeManager>
#include <bb/system/InvokeRequest>
#include <bb/data/JsonDataAccess>
#include <bb/cascades/Label>
#include <bb/cascades/ListItemListener>
#include <bb/cascades/ListView>
#include <bb/cascades/Menu>
#include <bb/system/NfcShareDataContent>
#include <bb/system/NfcShareManager>
#include <bb/cascades/Page>
#include <bb/cascades/SettingsActionItem>
#include <bb/cascades/Sheet>
#include <bb/cascades/Slider>
#include <bb/cascades/StackLayout>
#include <bb/cascades/SystemDefaults>
//#include <bb/system/SystemPrompt>
#include <bb/system/SystemToast>
#include <bb/cascades/TabbedPane>
#include <bb/cascades/TapHandler>
#include <bb/cascades/TextField>
#include <bb/cascades/TitleBar>

#include <bb/platform/bbm/Context>
#include <bb/platform/bbm/MessageService>
#include <bb/platform/bbm/UserProfile>

using namespace bb::cascades;
using namespace bb::system;
using namespace bb::data;


//class QTranslator;

/*!
 * @brief Application object
 *
 *
 */

class ApplicationUI : public QObject
{
	Q_OBJECT
public:
	ApplicationUI(bb::cascades::Application *app);
	virtual ~ApplicationUI();
private slots:
	void changeFB();
	void changeLI();
	void clearTheList();
	void deleteSelected();
	void displayHelp();
	void displayInfo();
	void displaySettings();
	//void finishedSending(bb::system::NfcShareSuccess::Type);
	void getFbID();
	void getLiID();
	void goToAppPage();
	void goToPrivacyPolicy();
	void goToRubus();
	void goToSV();
	void handleConnector(QString);
	void handleExit();
	void handleHelpSlider(float);
	void handleHelpSliderImm(float);
	//void handleLocPrompt(bb::system::SystemUiResult::Type);
	void handleTabChange(bb::cascades::Tab *);
	void handleToastFinish();
	//void invokeFinished();
	//void onDataModelUpdated();
	void onInvoked(const bb::system::InvokeRequest&);
	void onListViewTriggered(const QVariantList);
	void openFB();
	void openLI();
	//void openLocPrompt();
	void registrationStateUpdated(bb::platform::bbm::RegistrationState::Type);
	void setContentForHelp();
	void setContentToShare();
	void shareApp();
	void shareFBChanged(bool);
	void shareLIChanged(bool);
	void submitted();
private:

	ActionItem *clearListAction;//, *saveAction;
	ArrayDataModel *dataModel, *tempList;
	CheckBox *shareFB, *shareLI;
	Container *savedRoot, *emptyStateContainer;
	DeleteActionItem *deleteAction;
	ImageButton *fbButton, *liButton;
	//ImageView *helpImage;
	InvokeManager *invokeManager;
	Label *shareFBL, *shareLIL;
	Label *tapMessage, *rNameLabel;
	Label *helpLabel;
	ListView *listView;
	NfcShareManager *shareManager;
	Page *sharePage, *savedPage, *infoPage, *helpPage, *settingsPage;
	Sheet *appSheet;
	Slider *helpSlider;
	//SystemPrompt *locationPrompt;
	SystemToast *deletedToast, *savedToast, *bbmToast;
	Tab *shareTab, *savedTab;
	TabbedPane *tabChooser;
	TextField *nameField, *fbField, *liField;

	int nItemsSelected, nBackup, helpLevel;
	int *tempPos;
	bool fbSet, liSet, listCleared;
	bool helpFirstTime, settingsFirstTime, infoFirstTime;

	QSettings *appSavedSettings;
	//QString textToShare;
	QString userName, userFbID, userLiID;//, lastSavedLoc; //TO BE SAVED AT EXIT
	QString rName, rfbID, rliID;

	bb::platform::bbm::UserProfile *m_userProfile;
	bb::platform::bbm::Context *m_context;
	bb::platform::bbm::MessageService *m_messageService;

	//QTranslator* m_pTranslator;
	//bb::cascades::LocaleHandler* m_pLocaleHandler;
};

class MyItemClass: public bb::cascades::CustomControl, public ListItemListener
{
Q_OBJECT

public:
    MyItemClass(Container *parent=0);
    ~MyItemClass();

    void updateItem(const QString, const QString, const QString);

    void select(bool select);

    void reset(bool selected, bool activated);

    void activate(bool activate);

private:
    ImageButton *fbImage, *liImage;
    Label *nameLabel;
   // Label *metPlaceLabel;
    QString fbID, liID;

    Container *mHighlighContainer;

private slots:
	void connectToFB();
    void connectToLI();
};


class MyItemClassFactory: public bb::cascades::ListItemProvider
{
public:
    MyItemClassFactory();

    VisualNode *createItem(ListView*, const QString &);

    void updateItem(ListView*, VisualNode*, const QString&,
                    const QVariantList&, const QVariant&);
};

#endif /* ApplicationUI_HPP_ */
