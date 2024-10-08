#include "createbankaccount.h"
#include "ui_createbankaccount.h"
#include "user.h"
#include "loginsignin.h"
#include "cardinfo.h"
#include "changepassword.h"
#include "viewbalance.h"
#include "transfer.h"

#include <QKeyEvent>

CreateBankAccount::CreateBankAccount(User users, QWidget *parent) : QWidget(parent) , ui(new Ui::CreateBankAccount) {
    ui->setupUi(this);

    //disable maximize
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);

    //set user
    this->users = users;

    addInfo();

    hideError();

    //click to open pages
    if (users.getBankAccountNum() != 0) {
        connect(ui->changePasswordPB, SIGNAL(clicked()), this, SLOT(openChangePasswordPage()));
        connect(ui->viewBalancePB, SIGNAL(clicked()), this, SLOT(openViewBalancePage()));
        connect(ui->transferPB, SIGNAL(clicked()), this, SLOT(openTransferPage()));
    }

    //click create push button
    connect(ui->createPB, SIGNAL(clicked()), this, SLOT(checkCreateBankAccount()));

    //click logout push button
    connect(ui->logoutPB, SIGNAL(clicked()), this, SLOT(openLogoutPage()));

    //click enter for create
    connect(ui->initialBalanceLE, SIGNAL(returnPressed()), ui->createPB, SLOT(click()));
    connect(ui->fourDigitPasswordLE, SIGNAL(returnPressed()), ui->createPB, SLOT(click()));
    connect(ui->fixedPasswordLE, SIGNAL(returnPressed()), ui->createPB, SLOT(click()));

    //set cursor
    ui->bankAccountTypeCB->setFocus();
}
CreateBankAccount::~CreateBankAccount() {
    delete ui;
}
void CreateBankAccount::addInfo() {
    ui->firstNameST->setText(users.getName());
    ui->lastNameST->setText(users.getFamily());
    ui->nationalCodeST->setText(users.getNationalCode());
    ui->ageST->setText(QString::number(users.getAge()));
    ui->accountsNumST->setText(QString::number(users.getBankAccountNum()));
}

void CreateBankAccount::createPBClick() {
    CardInfo *np = new CardInfo(users);
    np->show();
    this->close();
}

void CreateBankAccount::hideError() {
    ui->balanceError->hide();
    ui->fourDigitPasswordError->hide();
    ui->fixedPasswordError->hide();
    ui->createNewBankAccountError->hide();
}

void CreateBankAccount::checkCreateBankAccount() {
    hideError();

    bool checkError = true;

    //for not changing checkError from false to true

    //if user has less than 5 bank accounts
    if (users.getBankAccountNum() >= 5) {
        ui->createNewBankAccountError->show();
        return;
    }

    if (checkBalanceField())
        checkError = false;
    if (check4DigitPasswordField())
        checkError = false;
    if (checkFixedPasswordField())
        checkError = false;

    if (checkError) {
        finalUserSet();
        createPBClick();
    }
}

bool CreateBankAccount::checkBalanceField() {
    if (ui->initialBalanceLE->text() == "") {
        ui->balanceError->setText("This field is empty");
        ui->balanceError->show();
        return true;
    }
    else if (checkNumber(ui->initialBalanceLE->text())) {
        ui->balanceError->setText("This field is invalid");
        ui->balanceError->show();
        return true;
    }
    else if (checkBalance(ui->initialBalanceLE->text().toLongLong())) {
        ui->balanceError->setText("This field must be between 50,000T and 1,000,000,000,000T");
        ui->balanceError->show();
        return true;
    }
    return false;
}

bool CreateBankAccount::check4DigitPasswordField() {
    if (ui->fourDigitPasswordLE->text() == "") {
        ui->fourDigitPasswordError->setText("This field is empty");
        ui->fourDigitPasswordError->show();
        return true;
    }
    else if (checkNumber(ui->fourDigitPasswordLE->text())) {
        ui->fourDigitPasswordError->setText("This field is invalid");
        ui->fourDigitPasswordError->show();
        return true;
    }
    else if (checkFourDigitPassword(ui->fourDigitPasswordLE->text())) {
        ui->fourDigitPasswordError->setText("This field must be 4 digits");
        ui->fourDigitPasswordError->show();
        return true;
    }
    return false;
}

bool CreateBankAccount::checkFixedPasswordField() {
    if (ui->fixedPasswordLE->text() != "") {
        if (checkNumber(ui->fixedPasswordLE->text())) {
            ui->fixedPasswordError->setText("This field is invalid");
            ui->fixedPasswordError->show();
            return true;
        }
        else if (checkFixedPassword(ui->fixedPasswordLE->text())) {
            ui->fixedPasswordError->setText("This field must be 4 to 12 digits");
            ui->fixedPasswordError->show();
            return true;
        }
    }
    return false;
}

bool CreateBankAccount::checkNumber(QString text) {
    for (int i = 0; i < text.length(); i++) {
        if ((text[i] < '0') || (text[i] > '9')) {
            return true;
        }
    }
    return false;
}

bool CreateBankAccount::checkBalance(long long int balance) {
    if (balance >= 50000 && balance <= 999999999999)
        return false;
    return true;
}

bool CreateBankAccount::checkFourDigitPassword(QString fourDigitPassword) {
    if (fourDigitPassword.size() == 4)
        return false;
    return true;
}

bool CreateBankAccount::checkFixedPassword(QString fixedPassword) {
    if (fixedPassword.size() >= 4 && fixedPassword.size() <= 12) {
        return false;
    }
    return true;
}

void CreateBankAccount::openChangePasswordPage() {
    ChangePassword *np = new ChangePassword(users);
    np->show();
    this->close();
}

void CreateBankAccount::openViewBalancePage() {
    ViewBalance *np = new ViewBalance(users);
    np->show();
    this->close();
}

void CreateBankAccount::openTransferPage() {
    Transfer *np = new Transfer(users);
    np->show();
    this->close();
}

void CreateBankAccount::openLogoutPage() {
    LoginSignin *np = new LoginSignin(users);
    np->show();
    this->close();
}

void CreateBankAccount::finalUserSet() {
    //set bank account number
    users.setBankAccountNum(users.getBankAccountNum() + 1);

    //set bank account type
    if (ui->bankAccountTypeCB->currentText() == "Saving")
        bankAccounts.setBankType(saving);
    else if (ui->bankAccountTypeCB->currentText() == "Current")
        bankAccounts.setBankType(current);
    else if (ui->bankAccountTypeCB->currentText() == "Loan")
        bankAccounts.setBankType(loan);

    //set initial balance
    bankAccounts.setBalance(ui->initialBalanceLE->text().toLongLong());

    //set 4 digit password
    cards.setFourDigitPassword(ui->fourDigitPasswordLE->text());

    //set fixed password
    if (ui->fixedPasswordLE->text() != "") {
        cards.setFixedPassword(ui->fixedPasswordLE->text());
        cards.setHaveFixedPassword(true);
    }
    else
        cards.setHaveFixedPassword(false);

    //set to bank account
    bankAccounts.setBankCard(cards);

    //set to user
    users.setSingleBankAccount(bankAccounts, users.getBankAccountNum() - 1);

    //set to list of users
    users.updateUserDataInList(users.getNationalCode());
}

void CreateBankAccount::keyPressEvent(QKeyEvent *event) {
    QWidget *focusedWidget = QApplication::focusWidget();

    if (focusedWidget == ui->bankAccountTypeCB) {
        if(event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
            int currentIndex = ui->bankAccountTypeCB->currentIndex();
            int nextIndex = (currentIndex + 1) % ui->bankAccountTypeCB->count();
            ui->bankAccountTypeCB->setCurrentIndex(nextIndex);
        }
    }
    else {
        QWidget::keyPressEvent(event);
    }
}
