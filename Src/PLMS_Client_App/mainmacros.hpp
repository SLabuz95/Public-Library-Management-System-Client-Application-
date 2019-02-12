#ifndef MAINMACROS_HPP
#define MAINMACROS_HPP

// ------------------ Macros ----------------------------------------------------------------------------
// Main Application Macros --------------------------------------------------------------------
#define APP_NAME ("Aplikacja biblioteki publicznej")
#define APP_VERSION ("ver 1.0")
// --------------------------------------------------------------------------------------------

// Memory Pointer Macros ------------------------------------------------------------------------------
#define SET_PTR_DO(ptr, newPtr) {if(ptr) {delete ptr; ptr = nullptr;} ptr = newPtr;}
#define SET_PTR_DOA(ptrA, newPtrA) {if(ptrA) {delete []ptrA; ptrA = nullptr;}; ptrA = newPtrA;}
#define SET_PTR_NDO(ptr, newPtr) {ptr = newPtr;}
// ---------------------------------------------------------------------------------------------

// Main Macros For Windows --------------------------------------------------------------------------
#define WINDOW_STATUS_SAVE(windowStatusPTR) *(windowStatusPTR + 1) = *windowStatusPTR;
// -----------------------------------------------------------------------------------------------

// Text Macros For Menu ----------------------------------------------------------------------------
#define APPLICATION_MENU_TEXT ("Program")
#define TOOLS_MENU_TEXT ("Narzędzia")
#define HELP_MENU_TEXT ("Pomoc")

// Application Menu Actions
#define APPLICATION_MENU_LOGIN_ACTION_TEXT ("Zaloguj")
#define APPLICATION_MENU_REGISTER_ACTION_TEXT ("Stwórz konto")
#define APPLICATION_MENU_QUIT_ACTION_TEXT ("Wyjdź")

// Help Menu Actions
#define HELP_MENU_APP_INFO_ACTION_TEXT ("O programie")
#define HELP_MENU_AUTHORS_ACTION_TEXT ("Autorzy")

// -------------------------------------------------------------------------------------------------------------

// Icon Files for Tool Bar-----------------------------------------------------------------------------------------------------
#define TOOL_BAR_LOGIN_ACTION_ICON QIcon(QString(":/icons/helpIcon.png"))
#define TOOL_BAR_REGISTER_ACTION_ICON QIcon(QString(":/icons/helpIcon.png"))
#define TOOL_BAR_HELP_ACTION_ICON QIcon(QString(":/icons/helpIcon.png"))

// --------------------------------------------------------------------------------------------------------------------

// Icon or PixMap Files for Prompt Panel ---------------------------------------------------------------------------------
#define PROMPT_PANEL_CLOSE_BUTTON_PIXMAP QPixmap(QString(":/icons/closeButtonIcon.png"))
#define PROMPT_PANEL_MINIMIZE_BUTTON_INFO_ICON QPixmap(QString(":/icons/infoPromptIcon.png"))
#define PROMPT_PANEL_MINIMIZE_BUTTON_ERROR_ICON QPixmap(QString(":/icons/errorPromptIcon.png"))
#define PROMPT_PANEL_MINIMIZE_BUTTON_UP_EXTEND_ARROW_ICON QPixmap(QString(":/icons/upExtendArrowIcon.png"))
#define PROMPT_PANEL_MINIMIZE_BUTTON_DOWN_EXTEND_ARROW_ICON QPixmap(QString(":/icons/downExtendArrowIcon.png"))
#define PROMPT_PANEL_MAXIMIZE_BUTTON_UP_EXTEND_ARROW_ICON QPixmap(QString(":/icons/upExtendArrowIcon.png"))
#define PROMPT_PANEL_MAXIMIZE_BUTTON_DOWN_EXTEND_ARROW_ICON QPixmap(QString(":/icons/downExtendArrowIcon.png"))
#define PROMPT_ELEMENT_EXPAND_BUTTON_UP_EXTEND_ARROW_ICON QPixmap(QString(":/icons/upExtendArrowIcon.png"))
#define PROMPT_ELEMENT_EXPAND_BUTTON_DOWN_EXTEND_ARROW_ICON QPixmap(QString(":/icons/downExtendArrowIcon.png"))
// -------------------------------------------------------------------------------------------------------------

// Server Status Text Generator ---------------------------------------------------------------------------------
#define SERVER_STATUS_TEXT(status) (QString("Stan serwera: ") + status)
#define SERVER_STATUS_NO_CONNECTION_TEXT (QString("Brak połączenia"))
#define SERVER_STATUS_CONNECTION_TEXT (QString("Połączony"))
#define SERVER_STATUS_INITIALIZATION_TEXT (QString("Inicjowanie"))
//--------------------------------------------------------------------------------------------------------------

// Status Bar Macros -------------------------------------------------------------------------------------------
#define STATUS_BAR_READY_TEXT (QString("Gotowy"))
// ------------------------------------------------------------------------------------------------------------

// User Tab and Tab Bar Macros --------------------------------------------------------------------------------------------
#define USER_TAB_CLOSE_BUTTON_ICON (QPixmap(QString(":/icons/closeButtonIcon.png")))
#define TAB_BAR_LEFT_EXTEND_BUTTON_ICON (QPixmap(QString(":/icons/leftExtendArrowIcon.png")))
#define TAB_BAR_RIGHT_EXTEND_BUTTON_ICON (QPixmap(QString(":/icons/rightExtendArrowIcon.png")))
// ----------------------------------------------------------------------------------------

// App Window Central Panel -----------------------------------------------------------------------------------------------
// App Window Login Panel --------------------------
#define APP_WINDOW_LOGIN_PANEL_LOGIN_TITLE_TEXT (QString("Panel logowania"))
#define APP_WINDOW_LOGIN_PANEL_LOGIN_NAME_TEXT (QString("Nazwa użytkownika:"))
#define APP_WINDOW_LOGIN_PANEL_LOGIN_PASSWORD_TEXT (QString("Hasło:"))
#define APP_WINDOW_LOGIN_PANEL_LOGIN_PASSWORD_HIDDEN_TEXT (QString("Ukryj hasło"))
#define APP_WINDOW_LOGIN_PANEL_LOGIN_BUTTON_TEXT (QString("Zaloguj"))
#define APP_WINDOW_LOGIN_PANEL_REGISTER_BUTTON_TEXT (QString("Utwórz konto"))
// -----------------------------------------------------------------------------------------------------------------------

// App Window Register Panel --------------------------
#define APP_WINDOW_REGISTER_PANEL_REGISTER_TITLE_TEXT (QString("Panel rejestracji konta"))
#define APP_WINDOW_REGISTER_PANEL_REGISTER_BUTTON_TEXT (QString("Zarejestuj"))
#define APP_WINDOW_REGISTER_PANEL_CANCEL_BUTTON_TEXT (QString("Anuluj"))
// -----------------------------------------------------------------------------------------------------------------------

// App Window Logged In Panel --------------------------
#define APP_WINDOW_LOGGED_IN_PANEL_CONTROL_PANEL_YOUR_ACCOUNT_TEXT (QString("Twoje konto"))
#define APP_WINDOW_LOGGED_IN_PANEL_CONTROL_PANEL_USERS_TEXT (QString("Użytkownicy"))
#define APP_WINDOW_LOGGED_IN_PANEL_CONTROL_PANEL_BOOKS_TEXT (QString("Książki"))
#define APP_WINDOW_LOGGED_IN_PANEL_CONTROL_PANEL_ADD_BOOK_TEXT (QString("Dodaj książkę"))
#define APP_WINDOW_LOGGED_IN_PANEL_CONTROL_PANEL_ADD_USER_TEXT (QString("Dodaj użytkownika"))
#define APP_WINDOW_LOGGED_IN_PANEL_CONTROL_PANEL_BOOK_LOG_TEXT (QString("Historia"))
#define APP_WINDOW_LOGGED_IN_PANEL_CONTROL_PANEL_LOGOUT_TEXT (QString("Wyloguj"))
#define APP_WINDOW_LOGGED_IN_PANEL_CONTROL_PANEL_READERS_TEXT (QString("Czytelnicy"))
#define APP_WINDOW_LOGGED_IN_PANEL_CONTROL_PANEL_YOUR_BOOKS_TEXT (QString("Twoje książki"))
#define APP_WINDOW_LOGGED_IN_PANEL_CONTROL_PANEL_LIBRARY_TEXT (QString("Biblioteka"))
// -----------------------------------------------------------------------------------------------------------------------

// Operation Panel
#define OPERATION_PANEL_YOUR_ACCOUNT_TITLE (QString("Twoje konto"))
#define OPERATION_PANEL_YOUR_ACCOUNT_CHANGE_DATA_BUTTON_TEXT (QString("Edytuj dane"))
#define OPERATION_PANEL_YOUR_ACCOUNT_ACCEPT_BUTTON_TEXT (QString("Zatwierdź"))
#define OPERATION_PANEL_YOUR_ACCOUNT_CANCEL_BUTTON_TEXT (QString("Anuluj"))
#define OPERATION_PANEL_YOUR_ACCOUNT_REMOVE_ACCOUNT_BUTTON_TEXT (QString("Usuń konto"))
#define OPERATION_PANEL_USER_DATA_TITLE_TEXT (QString("Dane użytkownika"))
#define OPERATION_PANEL_BOOK_PANEL_USER_DATA_BUTTON_TEXT (QString("Panel książek"))
#define OPERATION_PANEL_CHANGE_DATA_USER_DATA_BUTTON_TEXT (QString("Zmień dane"))
#define OPERATION_PANEL_REMOVE_ACCOUNT_USER_DATA_BUTTON_TEXT (QString("Usuń konto"))
#define OPERATION_PANEL_USER_DATA_ACCEPT_BUTTON_TEXT (QString("Zatwierdź"))
#define OPERATION_PANEL_USER_DATA_CANCEL_BUTTON_TEXT (QString("Anuluj"))
#define OPERATION_LIST_NO_ELEMENTS_BOOKS_INFO_TEXT (QString("Brak książek"))
#define OPERATION_LIST_NO_ELEMENTS_MY_BOOKS_INFO_TEXT (QString("Brak wypożyczonych książek"))
#define OPERATION_LIST_NO_ELEMENTS_USERS_INFO_TEXT (QString("Brak użytkowników"))
#define OPERATION_LIST_NO_ELEMENTS_READERS_INFO_TEXT (QString("Brak czytelników"))

#define OPERATION_PANEL_BOOK_DATA_TITLE_TEXT (QString("Panel książek"))
#define OPERATION_PANEL_CHANGE_DATA_BOOK_DATA_BUTTON_TEXT (QString("Zmień dane"))
#define OPERATION_PANEL_REMOVE_BOOK_DATA_BUTTON_TEXT (QString("Usuń książkę"))
#define OPERATION_PANEL_BOOK_DATA_ACCEPT_BUTTON_TEXT (QString("Zatwierdź"))
#define OPERATION_PANEL_BOOK_DATA_CANCEL_BUTTON_TEXT (QString("Anuluj"))

#define OPERATION_PANEL_ADD_USER_TITLE_TEXT (QString("Dodawanie użytkownika"))
#define OPERATION_PANEL_ADD_USER_ADD_BUTTON_TEXT (QString("Dodaj"))
#define OPERATION_PANEL_ADD_USER_CANCEL_BUTTON_TEXT (QString("Anuluj"))

#define OPERATION_PANEL_ADD_BOOK_TITLE_TEXT (QString("Dodawanie książki"))
#define OPERATION_PANEL_ADD_BOOK_ADD_BUTTON_TEXT (QString("Dodaj"))
#define OPERATION_PANEL_ADD_BOOK_CANCEL_BUTTON_TEXT (QString("Anuluj"))

// -------------------------------------------------------------------------------------------------------------

// Data Panel--------------------------------------------------------------------------------------------
// User Data Panel ----------------------------------------------------------------------------------------------
#define USER_DATA_PANEL_USER_NAME_TEXT (QString("Nazwa użytkownika: "))
#define USER_DATA_PANEL_PASSWORD_TEXT (QString("Hasło: "))
#define USER_DATA_PANEL_FIRST_NAME_TEXT (QString("Imie: "))
#define USER_DATA_PANEL_SECOND_NAME_TEXT (QString("Drugie imie: "))
#define USER_DATA_PANEL_SURNAME_TEXT (QString("Nazwisko: "))
#define USER_DATA_PANEL_PESEL_TEXT (QString("Pesel: "))
// ---------------------------------------------------------------------------------------------------------

// Book Data Panel ----------------------------------------------------------------------------------------------
#define BOOK_DATA_PANEL_BOOK_TITLE_TEXT (QString("Tytuł książki: "))
#define BOOK_DATA_PANEL_BOOK_AUTHOR_TEXT (QString("Autor: "))
#define BOOK_DATA_PANEL_PUBLISHER_TEXT (QString("Wydawca: "))
#define BOOK_DATA_PANEL_EDITION_TEXT (QString("Wydanie: "))
#define BOOK_DATA_PANEL_BOOK_TYPE_TEXT (QString("Gatunek: "))
#define BOOK_DATA_PANEL_STATUS_TEXT (QString("Status książki: "))
#define BOOK_DATA_PANEL_RESERVED_DATE_TEXT (QString("Rezerwacja wygasa: "))
#define BOOK_DATA_PANEL_CHECKOUT_DATE_TEXT (QString("Wypożyczenie wygasa: "))
#define BOOK_DATA_PANEL_EXPIRED_DATE_TEXT (QString("Wypożyczenie wygasło: "))
// ---------------------------------------------------------------------------------------------------------

// Operation Elements Text Generators-----------------------------------------------------------------------------
#define TEXT_GENERATOR_ELEMENT_READER (QString("Personalia: ") + user->getParam(USER_FIRST_NAME) +  ((user->getParam(USER_SECOND_NAME).isEmpty())? QString() : QString(" ") + user->getParam(USER_SECOND_NAME)) + QString(" ") + user->getParam(USER_SURNAME) + QString("\nPesel: ") + user->getParam(USER_PESEL) + QString("\nIlość wypożyczonych/zarezerwowanych książek: ") + QString::number(user->getNumbOfBookId()))
#define TEXT_GENERATOR_ELEMENT_USER (QString("Personalia: ") + user->getParam(USER_FIRST_NAME) +  ((user->getParam(USER_SECOND_NAME).isEmpty())? QString() : QString(" ") + user->getParam(USER_SECOND_NAME)) + QString(" ") + user->getParam(USER_SURNAME) + QString("\nPesel: ") + user->getParam(USER_PESEL) + ((user->getUserPermissions() != USER_PERMISSIONS_ADMIN)? QString("\nIlość wypożyczonych/zarezerwowanych książek: ") + QString::number(user->getNumbOfBookId()) : QString())  + QString("\nPoziom uprawnień: ") + userPerm)
#define TEXT_GENERATOR_ELEMENT_MY_BOOKS (QString("Indeks: ") + book->getParam(BOOK_ID) + QString("\nTytuł: ") + book->getParam(BOOK_TITLE) + QString("\nWydawca: ") + book->getParam(BOOK_PUBLISHER) + QString("\nWydanie: ") + book->getParam(BOOK_EDITION) + bookType + additionalText)
#define TEXT_GENERATOR_ELEMENT_LIBRARY (QString("Indeks: ") + book->getParam(BOOK_ID) + QString("\nTytuł: ") + book->getParam(BOOK_TITLE) + QString("\nWydawca: ") + book->getParam(BOOK_PUBLISHER) + QString("\nWydanie: ") + book->getParam(BOOK_EDITION)+ bookType + additionalText)
#define TEXT_GENERATOR_ELEMENT_BOOKS (QString("Indeks: ") + book->getParam(BOOK_ID) + QString("\nTytuł: ") + book->getParam(BOOK_TITLE) + QString("\nWydawca: ") + book->getParam(BOOK_PUBLISHER) + QString("\nWydanie: ") + book->getParam(BOOK_EDITION) + bookType + additionalText)
#define TEXT_GENERATOR_ELEMENT_BOOK_LOG (action + QString("\nData i czas działania: ") + bookLog->getParam(BOOK_LOG_ACTION_DATE_TIME) + QString("\nPersonalia: ") + bookLog->getParam(BOOK_LOG_USER_FIRST_NAME) +  QString(" ") + bookLog->getParam(BOOK_LOG_USER_SURNAME) + QString("\nPesel: ") + bookLog->getParam(BOOK_LOG_USER_PESEL) + perm)

// -------------------------------------------------------------------------------------------------------------

// Filter Panel
#define FILTER_TITLE_TEXT (QString("Wyszukiwarka"))
#define FILTER_ADD_FILTER_BUTTON_TEXT (QString("Dodaj"))
#define FILTER_FIND_BUTTON_TEXT (QString("Wyszukaj"))
#define FILTER_REMOVE_BUTTON_ICON (QPixmap(QString(":/icons/closeButtonIcon.png")))

// Dialog Change Password
#define DIALOG_CHANGE_PASSWORD_TITLE_LABEL_TEXT (QString("Zmiana hasła"))
#define DIALOG_CHANGE_PASSWORD_OLD_PASS_LABEL_TEXT (QString("Stare hasło:"))
#define DIALOG_CHANGE_PASSWORD_NEW_PASS_LABEL_TEXT (QString("Nowe hasło:"))
#define DIALOG_CHANGE_PASSWORD_ACCEPT_BUTTON_TEXT (QString("Zatwierdź"))
#define DIALOG_CHANGE_PASSWORD_CANCEL_BUTTON_TEXT (QString("Anuluj"))

// Dialog Book Panel
#define DIALOG_BOOK_PANEL_USERS_BOOKS_BUTTON_TEXT (QString("Książki użytkownika"))
#define DIALOG_BOOK_PANEL_CHECK_OUT_BUTTON_TEXT (QString("Wypożycz"))
#define DIALOG_BOOK_PANEL_CLOSE_BUTTON_TEXT (QString("Zamknij"))

// Dialog Add Comment Panel
#define DIALOG_ADD_COMMENT_PANEL_TITLE_TEXT (QString("Dodaj komentarz"))
#define DIALOG_EDIT_COMMENT_PANEL_TITLE_TEXT (QString("Edytuj komentarz"))
#define DIALOG_ADD_COMMENT_ACCEPT_BUTTON_TEXT (QString("Zatwierdź"))
#define DIALOG_ADD_COMMENT_CANCEL_BUTTON_TEXT (QString("Anuluj"))

// Dialog Check Password Panel
#define DIALOG_CHECK_PASSWORD_PANEL_TITLE_TEXT (QString("Podaj hasło"))
#define DIALOG_CHECK_PASSWORD_PANEL_PASSWORD_LABEL_TEXT (QString("Hasło:"))
#define DIALOG_CHECK_PASSWORD_ACCEPT_BUTTON_TEXT (QString("Zatwierdź"))
#define DIALOG_CHECK_PASSWORD_CANCEL_BUTTON_TEXT (QString("Anuluj"))
// -----------------------------------------------------------------------------------------------------------------

#endif // MAINMACROS_HPP
