#include"appwindowloginpanel.hpp"

AppWindowLoginPanel::AppWindowLoginPanel(AppWindow* parent)
    : AppWindowCentralPanel(parent),
      loginTitleLabel(this),
      loginNameLabel(this),
      loginNameField(true, nullptr, false, this, QString(), false),
      loginPasswordLabel(this),
      loginPasswordField(true, nullptr, false, this, QString(), false),
      passwordHiddenCB(this),
      loginButton(this),
      registerButton(this)
{
    init();
    setWindow();
    createWidgets();
    createLayout();
    connectAll();
}

AppWindowLoginPanel::~AppWindowLoginPanel(){
    disconnectAll();
    deleteWidgets();
}

void AppWindowLoginPanel::init(){
    passwordHiddenCB.setChecked(true);
}

void AppWindowLoginPanel::setWindow(){
    // Empty
}

void AppWindowLoginPanel::createWidgets(){
    // Empty
}

void AppWindowLoginPanel::createLayout(){
    // Login Title Label Layout
    loginTitleLabel.setText(APP_WINDOW_LOGIN_PANEL_LOGIN_TITLE_TEXT);
    loginTitleLabel.setGeometry(APP_WINDOW_LOGIN_PANEL_LOGIN_TITLE_X, APP_WINDOW_LOGIN_PANEL_LOGIN_TITLE_Y, APP_WINDOW_LOGIN_PANEL_LOGIN_TITLE_WIDTH, APP_WINDOW_LOGIN_PANEL_LOGIN_TITLE_HEIGHT);
    loginTitleLabel.setStyleSheet("background: transparent;");

    // Login Name Label Layout
    loginNameLabel.setText(APP_WINDOW_LOGIN_PANEL_LOGIN_NAME_TEXT);
    loginNameLabel.setGeometry(APP_WINDOW_LOGIN_PANEL_LOGIN_NAME_LABEL_X, APP_WINDOW_LOGIN_PANEL_LOGIN_NAME_LABEL_Y, APP_WINDOW_LOGIN_PANEL_LOGIN_NAME_LABEL_WIDTH, APP_WINDOW_LOGIN_PANEL_LOGIN_NAME_LABEL_HEIGHT);

    // Login Name Field Layout
    loginNameField.setGeometry(APP_WINDOW_LOGIN_PANEL_LOGIN_NAME_FIELD_X, APP_WINDOW_LOGIN_PANEL_LOGIN_NAME_FIELD_Y, APP_WINDOW_LOGIN_PANEL_LOGIN_NAME_FIELD_WIDTH, APP_WINDOW_LOGIN_PANEL_LOGIN_NAME_FIELD_HEIGHT);

    // Login Password Label Layout
    loginPasswordLabel.setText(APP_WINDOW_LOGIN_PANEL_LOGIN_PASSWORD_TEXT);
    loginPasswordLabel.setGeometry(APP_WINDOW_LOGIN_PANEL_PASSWORD_LABEL_X, APP_WINDOW_LOGIN_PANEL_PASSWORD_LABEL_Y, APP_WINDOW_LOGIN_PANEL_PASSWORD_LABEL_WIDTH, APP_WINDOW_LOGIN_PANEL_PASSWORD_LABEL_HEIGHT);

    // Login Password Field Layout
    loginPasswordField.setGeometry(APP_WINDOW_LOGIN_PANEL_PASSWORD_FIELD_X, APP_WINDOW_LOGIN_PANEL_PASSWORD_FIELD_Y, APP_WINDOW_LOGIN_PANEL_PASSWORD_FIELD_WIDTH, APP_WINDOW_LOGIN_PANEL_PASSWORD_FIELD_HEIGHT);

    // Login Password Hidden CheckBox
    passwordHiddenCB.setText(APP_WINDOW_LOGIN_PANEL_LOGIN_PASSWORD_HIDDEN_TEXT);
    passwordHiddenCB.setGeometry(APP_WINDOW_LOGIN_PANEL_PASSWORD_HIDDEN_CHECKBOX_X, APP_WINDOW_LOGIN_PANEL_PASSWORD_HIDDEN_CHECKBOX_Y, APP_WINDOW_LOGIN_PANEL_PASSWORD_HIDDEN_CHECKBOX_WIDTH, APP_WINDOW_LOGIN_PANEL_PASSWORD_HIDDEN_CHECKBOX_HEIGHT);

    // Login Button Text
    loginButton.setText(APP_WINDOW_LOGIN_PANEL_LOGIN_BUTTON_TEXT);
    loginButton.setGeometry(APP_WINDOW_LOGIN_PANEL_LOGIN_BUTTON_X, APP_WINDOW_LOGIN_PANEL_LOGIN_BUTTON_Y, APP_WINDOW_LOGIN_PANEL_LOGIN_BUTTON_WIDTH, APP_WINDOW_LOGIN_PANEL_LOGIN_BUTTON_HEIGHT);

    // Register Button Text
    registerButton.setText(APP_WINDOW_LOGIN_PANEL_REGISTER_BUTTON_TEXT);
    registerButton.setGeometry(APP_WINDOW_LOGIN_PANEL_REGISTER_BUTTON_X, APP_WINDOW_LOGIN_PANEL_REGISTER_BUTTON_Y, APP_WINDOW_LOGIN_PANEL_REGISTER_BUTTON_WIDTH, APP_WINDOW_LOGIN_PANEL_REGISTER_BUTTON_HEIGHT);
}

void AppWindowLoginPanel::deleteWidgets(){
    // Empty
}

void AppWindowLoginPanel::connectAll(){
    // Login Name Field Connect
    loginNameField.installEventFilter(this);

    // Login Password Field Connect
    loginPasswordField.installEventFilter(this);

    // Password Hidden Check Box Connect
    passwordHiddenCB.installEventFilter(this);

    // Login Button Connect
    loginButton.installEventFilter(this);

    // Register Button Connect
    registerButton.installEventFilter(this);
}

void AppWindowLoginPanel::disconnectAll(){

}

void AppWindowLoginPanel::loginButtonPressed(){

}

void AppWindowLoginPanel::registerButtonPressed(){

}

void AppWindowLoginPanel::passwordHiddenCBPressed(){

}

bool AppWindowLoginPanel::loginNameFieldKeyPressed(){

}

bool AppWindowLoginPanel::loginPasswordKeyPressed(){

}

void AppWindowLoginPanel::reload(){

}

bool AppWindowLoginPanel::eventMatching(QObject* obj, QEvent* ev){

}


