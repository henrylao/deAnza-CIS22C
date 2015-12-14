// Thomas Tang
// Yuan Zheng
// CIS22C Lab1 Bag Project
// Currencies.h


#ifndef CURRENCIES_
#define CURRENCIES_
#include "Currency.h"



class Dollar : public Currency {
public:
	Dollar();
	Dollar(int _wholePart, int _subPart);
};
Dollar::Dollar() : Currency("Dollar", 0, 0, "Cents") {
}
Dollar::Dollar(int _wholePart, int _subPart) : Currency("Dollar", _wholePart, _subPart, "Cents") {
}


class Euro : public Currency {
public:
	Euro();
	Euro(int _wholePart, int _subPart);
};
Euro::Euro() : Currency("Euro", 0, 0, "Cents") {
}
Euro::Euro(int _wholePart, int _subPart) : Currency("Euro", _wholePart, _subPart, "Cents") {
}


class Franc : public Currency {
public:
	Franc();
	Franc(int _wholePart, int _subPart);
};
Franc::Franc() : Currency("Franc", 0, 0, "Centimes") {
}
Franc::Franc(int _wholePart, int _subPart) : Currency("Franc", _wholePart, _subPart, "Centimes") {
}


class Peso : public Currency {
public:
	Peso();
	Peso(int _wholePart, int _subPart);
};
Peso::Peso() : Currency("Peso", 0, 0, "Centavos") {
}
Peso::Peso(int _wholePart, int _subPart) : Currency("Peso", _wholePart, _subPart, "Centavos") {
}


class Pound : public Currency {
public:
	Pound();
	Pound(int _wholePart, int _subPart);
};
Pound::Pound() : Currency("Pound", 0, 0, "Pence") {
}
Pound::Pound(int _wholePart, int _subPart) : Currency("Pound", _wholePart, _subPart, "Pence") {
}


class Rubel : public Currency {
public:
	Rubel();
	Rubel(int _wholePart, int _subPart);
};
Rubel::Rubel() : Currency("Rubel", 0, 0, "Kopeks") {
}
Rubel::Rubel(int _wholePart, int _subPart) : Currency("Rubel", _wholePart, _subPart, "Kopeks") {
}


class Rupee : public Currency {
public:
	Rupee();
	Rupee(int _wholePart, int _subPart);
};
Rupee::Rupee() : Currency("Rupee", 0, 0, "Paise") {
}
Rupee::Rupee(int _wholePart, int _subPart) : Currency("Rupee", _wholePart, _subPart, "Paise") {
}


class Shilling : public Currency {
public:
	Shilling();
	Shilling(int _wholePart, int _subPart);
};
Shilling::Shilling() : Currency("Shilling", 0, 0, "Cents") {
}
Shilling::Shilling(int _wholePart, int _subPart) : Currency("Shilling", _wholePart, _subPart, "Cents") {
}


class Won : public Currency {
public:
	Won();
	Won(int _wholePart, int _subPart);
};
Won::Won() : Currency("Won", 0, 0, "Chon") {
}
Won::Won(int _wholePart, int _subPart) : Currency("Won", _wholePart, _subPart, "Chon") {
}


class Yen : public Currency {
public:
	Yen();
	Yen(int _wholePart, int _subPart);
};
Yen::Yen() : Currency("Yen", 0, 0, "Sen") {
}
Yen::Yen(int _wholePart, int _subPart) : Currency("Yen", _wholePart, _subPart, "Sen") {
}

#endif // CURRENCIES_
