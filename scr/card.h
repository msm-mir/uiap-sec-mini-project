#ifndef CARD_H
#define CARD_H

#include <QString>

class Card {
private:
    QString cardNumber = "";
    QString ibanNumber = "";
    QString cvv2 = "";
    QString expirationDate = "";
    QString fourDigitPassword = "";
    QString fixedPassword = "";
    bool haveFixedPassword;
    QString oneTimePassword = "";
public:
    Card();
    ~Card();

    void setCardNumber(QString);
    void setIbanNumber(QString);
    void setCvv2(QString);
    void setExpirationDate(QString);
    void setFourDigitPassword(QString);
    void setFixedPassword(QString);
    void setHaveFixedPassword(bool);
    void setOneTimePassword(QString);

    QString getCardNumber();
    QString getIbanNumber();
    QString getCvv2();
    QString getExpirationDate();
    QString getFourDigitPassword();
    QString getFixedPassword();
    bool getHaveFixedPassword();
    QString getOneTimePassword();
};

#endif // CARD_H
