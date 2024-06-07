#include "createbankaccount.h"
#include "ui_createbankaccount.h"
#include "user.h"
#include "loginsignin.h"
#include "cardinfo.h"
#include "changepassword.h"
#include "viewbalance.h"
#include "transfer.h"

CreateBankAccount::CreateBankAccount(User users, QWidget *parent) : QWidget(parent) , ui(new Ui::CreateBankAccount) {
    ui->setupUi(this);

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
    connect(ui->createPB, SIGNAL(clicked()), this, SLOT(checkCreateAccount()));

    //click logout push button
    connect(ui->logoutPB, SIGNAL(clicked()), this, SLOT(openLogoutPage()));

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
    setUserBankAccountData();

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

void CreateBankAccount::checkCreateAccount() {
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
    else if (checkBalance(ui->initialBalanceLE->text())) {
        ui->balanceError->setText("This field must above 50,000T");
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
        if ((text[i] >= '0') && (text[i] <= '9')) {
            return false;
        }
    }
    return true;
}

bool CreateBankAccount::checkBalance(QString text) {
    if (text.size() >= 5) {
        if (text.size() == 5) {
            if (text[0] >= '5') return false;
            else return true;
        }
        return false;
    }
    return true;
}

bool CreateBankAccount::checkFourDigitPassword(QString text) {
    if (text.size() == 4)
        return false;
    return true;
}

bool CreateBankAccount::checkFixedPassword(QString text) {
    if (text.size() >= 4 && text.size() <= 12) {
        return false;
    }
    return true;
}

void CreateBankAccount::setUserBankAccountData() {
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
    bankAccounts.setBalance(ui->initialBalanceLE->text());

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
