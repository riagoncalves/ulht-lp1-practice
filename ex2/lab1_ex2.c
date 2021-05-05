#include <stdio.h>

char* getSign(int birthDay,int birthMonth) {
	if((birthDay >= 22 && birthMonth == 12) || (birthDay <= 19 && birthMonth == 1)) {
		return "Capricornio";
	}
	else if((birthDay >= 20 && birthMonth == 1) || (birthDay <= 18 && birthMonth == 2)) {
		return "Aquario";
	}
	else if((birthDay >= 19 && birthMonth == 2) || (birthDay <= 20 && birthMonth == 3)) {
		return "Peixes";
	}
	else if((birthDay >= 21 && birthMonth == 3) || (birthDay <= 19 && birthMonth == 4)) {
		return "Carneiro";
	}
	else if((birthDay >= 20 && birthMonth == 4) || (birthDay <= 20 && birthMonth == 5)) {
		return "Touro";
	}
	else if((birthDay >= 21 && birthMonth == 5) || (birthDay <= 20 && birthMonth == 6)) {
		return "Gemeos";
	}
	else if((birthDay >= 21 && birthMonth == 6) || (birthDay <= 22 && birthMonth == 7)) {
		return "Carangueijo";
	}
	else if((birthDay >= 23 && birthMonth == 7) || (birthDay <= 22 && birthMonth == 8)) {
		return "Leao";
	}
	else if((birthDay >= 23 && birthMonth == 8) || (birthDay <= 22 && birthMonth == 9)) {
		return "Virgem";
	}
	else if((birthDay >= 23 && birthMonth == 9) || (birthDay <= 22 && birthMonth == 10)) {
		return "Balanca";
	}
	else if((birthDay >= 23 && birthMonth == 10) || (birthDay <= 21 && birthMonth == 11)) {
		return "Escorpiao";
	}
	else if((birthDay >= 22 && birthMonth == 11) || (birthDay <= 21 && birthMonth == 12)) {
		return "Sagitario";
	}
	else {
		return "";
	}
} 

int getAge(int birthDay, int birthMonth, int birthYear, int dateDay, int dateMonth, int dateYear) {
	int yearDif = dateYear - birthYear;
	int monthDif = dateMonth - birthMonth;
	int dayDif = dateDay - birthDay;

	if(yearDif >= 0) {
		if(monthDif > 0) {
			return yearDif;
		}
		else if(monthDif == 0) {
			
			if(dayDif < 0) {
				return --yearDif;
			}
			else {
				return yearDif;
			}
		}
		else {
			return --yearDif;
		}
	}
	else {
		return 0;
	}
}

char* workCondition(int birthDay, int birthMonth, int birthYear, int dateDay, int dateMonth, int dateYear) {
	if(getAge(birthDay, birthMonth, birthYear, dateDay, dateMonth, dateYear) >= 66) {
		if(getAge(birthDay, birthMonth, birthYear, dateDay, dateMonth, dateYear) == 66) {
			if((dateMonth - birthMonth) < 5) {
				return "Apto para trabalhar";
			}
			else if((dateMonth - birthMonth) == 5) {
				if((dateDay - birthDay) >= 0) {
					return "Elegivel para reforma";
				}
				else {
					return "Apto para trabalhar";
				}
			}
			else {
				return "Elegivel para reforma";
			}
		}
		else {
			return "Elegivel para reforma";
		}
	}
	else if(getAge(birthDay, birthMonth, birthYear, dateDay, dateMonth, dateYear) >= 16) {
		return "Apto para trabalhar";
	}
	else if(getAge(birthDay, birthMonth, birthYear, dateDay, dateMonth, dateYear) < 16) {
		return "Nao tem idade para trabalhar";
	}
	else {
		return "Apto para trabalhar";
	}
}

int validDate(int day, int month, int year) {
	if(year < 1900 || year > 2020) {
		return 0;
	}

	if(month < 1 || month > 12) {
		return 0;
	}

	if(day >= 1) {
		if((day > 31) && (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)) {
			return 0;
		}
		else if ((day > 30) && (month == 4 || month == 6 || month == 9)) {
			return 0;
		}
		else if(month == 2) {
			if(((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)) {
				if(day > 29) {
					return 0;
				}
				else {
					return 1;
				}
			}
			else if(day > 28) {
				return 0;
			}
			else {
				return 1;
			}
		}
	}
	else {
		return 0;
	}

	return 1;
}

int validBirthday(int birthDay, int birthMonth, int birthYear, int dateDay, int dateMonth, int dateYear) {
	if(dateYear < birthYear) {
		return 0;
	}
	else if(getAge(birthDay, birthMonth, birthYear, dateDay, dateMonth, dateYear) < 0) {
		return 0;
	}
	else if(dateYear == birthYear) {
		if(dateMonth < birthMonth) {
			return 0;
		}
		else if(dateMonth == birthMonth) {
			if(dateDay >= birthDay) {
				return 1;
			}
			else {
				return 0;
			}
		}
		else {
			return 1;
		}
	}
	else {
		return 1;
	}
}

int main() {

	char option;
	int birthDay, birthMonth, birthYear, dateDay, dateMonth, dateYear;
	
	scanf("%c %d %d %d %d %d %d", &option, &birthDay, &birthMonth, &birthYear, &dateDay, &dateMonth, &dateYear);

	if(!validDate(birthDay, birthMonth, birthYear)) {
		puts("Data de nascimento invalida");
		return 0;
	}

	if(!validDate(dateDay, dateMonth, dateYear)) {
		puts("Data actual invalida");
		return 0;
	}

	if(!validBirthday(birthDay, birthMonth, birthYear, dateDay, dateMonth, dateYear)) {
		puts("Data actual inferior a data de nascimento");
		return 0;
	}
	
	switch (option)
	{
	case 'a':
		printf("%d anos\n", getAge(birthDay, birthMonth, birthYear, dateDay, dateMonth, dateYear));
		break;

	case 'z':
		printf("%s\n", getSign(birthDay, birthMonth));
		break;

	case 'r':
		printf("%s\n", workCondition(birthDay, birthMonth, birthYear, dateDay, dateMonth, dateYear));
		break;

	case 't':
		printf("%d anos\n", getAge(birthDay, birthMonth, birthYear, dateDay, dateMonth, dateYear));
		printf("%s\n", getSign(birthDay, birthMonth));
		printf("%s\n", workCondition(birthDay, birthMonth, birthYear, dateDay, dateMonth, dateYear));
		break;
	
	default:
		break;
	}

	return 0;
}