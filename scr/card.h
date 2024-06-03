#ifndef CARD_H
#define CARD_H

#include <QString>

class Card {
private:
    QString cardNumber;
    QString ibanNumber;
    QString cvv2;
    QString expirationDate;
    QString fourDigitPassword;
    QString fixedPassword;
    QString oneTimePassword;
public:
    Card();
    void setCardNumber(QString);
    void setIbanNumber(QString);
    void setCvv2(QString);
    void setExpirationDate(QString);
    void setFourDigitPassword(QString);
    void setFixedPassword(QString);
    void setOneTimePassword(QString);
    QString getCardNumber();
    QString getIbanNumber();
    QString getCvv2();
    QString getExpirationDate();
    QString getFourDigitPassword();
    QString getFixedPassword();
    QString getOneTimePassword();
};

#endif // CARD_H
