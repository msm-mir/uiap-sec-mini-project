#include "card.h"

Card::Card() {}
Card::~Card() {}
void Card::setCardNumber(QString cardNumber) {
    this->cardNumber = cardNumber;
}
void Card::setIbanNumber(QString ibanNumber) {
    this->ibanNumber = ibanNumber;
}
void Card::setCvv2(QString cvv2) {
    this->cvv2 = cvv2;
}
void Card::setExpirationDate(tm expirationDate) {
    this->expirationDate = expirationDate;
}
void Card::setFourDigitPassword(QString fourDigitPassword) {
    this->fourDigitPassword = fourDigitPassword;
}
void Card::setFixedPassword(QString fixedPassword) {
    this->fixedPassword = fixedPassword;
}
void Card::setHaveFixedPassword(bool haveFixedPassword) {
    this->haveFixedPassword = haveFixedPassword;
}
void Card::setOneTimePassword(QString oneTimePassword) {
    this->oneTimePassword = oneTimePassword;
}
QString Card::getCardNumber() {
    return this->cardNumber;
}
QString Card::getIbanNumber() {
    return this->ibanNumber;
}
QString Card::getCvv2() {
    return this->cvv2;
}
tm Card::getExpirationDate() {
    return this->expirationDate;
}
QString Card::getFourDigitPassword() {
    return this->fourDigitPassword;
}
QString Card::getFixedPassword() {
    return this->fixedPassword;
}
bool Card::getHaveFixedPassword() {
    return this->haveFixedPassword;
}
QString Card::getOneTimePassword() {
    return this->oneTimePassword;
}
