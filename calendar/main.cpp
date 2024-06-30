#pragma warning(disable : 4996)

#include<iostream>
#include<cmath>
#include<iomanip>
#include<ctime>

using namespace std;

//h = (q + floor(13(m + 1) / 5) + K + floor(K / 4) + floor(J / 4) + 5J) mod 7

int get_actual_month() {
	int month=1;
	time_t rawtime = time(0);
	char* date_time = ctime(&rawtime);
	char monthchar[4];

	strncpy(monthchar, date_time + 4, 3);
	monthchar[3] = '\0';
	if (strcmp(monthchar, "Jan") == 0) month = 1;
	if (strcmp(monthchar, "Feb") == 0) month = 2;
	if (strcmp(monthchar, "Mar") == 0) month = 3;
	if (strcmp(monthchar, "Apr") == 0) month = 4;
	if (strcmp(monthchar, "May") == 0) month = 5;
	if (strcmp(monthchar, "Jun") == 0) month = 6;
	if (strcmp(monthchar, "Jul") == 0) month = 7;
	if (strcmp(monthchar, "Aug") == 0) month = 8;
	if (strcmp(monthchar, "Sep") == 0) month = 9;
	if (strcmp(monthchar, "Oct") == 0) month = 10;
	if (strcmp(monthchar, "Nov") == 0) month = 11;
	if (strcmp(monthchar, "Dec") == 0) month = 12;

	return month;
}

int get_actual_year() {
	time_t rawtime = time(0);
	char* date_time = ctime(&rawtime);

	int year = atoi(date_time + 20);
	return year;
}

bool leap_year(int year=get_actual_year()) {
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
		return 1;
	return 0;
}


int get_firstday(int month=get_actual_month(), int year=get_actual_year()) {
	if (month < 3) month += 12, year--;
	int firstday = int(1 + floor(13 * (month + 1) / 5) + year % 100 + floor((year % 100) / 4) + floor(year / 100 / 4) + 5 * (year / 100)) % 7;
	return firstday;
}

void print_cal(int month=get_actual_month(), int year=get_actual_year(), int firstday=1) {
	
	int zile_max=31;

	bool leap = leap_year(year);

	if (month < 7)
		if (month % 2 == 0) zile_max = 30;
		else zile_max = 31;
	else if (month == 7 || month == 8) zile_max = 31;
	else
		if (month % 2 == 0) zile_max = 31;
		else zile_max = 30;

	if (month == 2)
		if (leap)
			zile_max = 29;
		else
			zile_max = 28;
	
	cout << ' ' << month << '/' << year << '\n';
	cout << " Mo Tu We Th Fr Sa Su\n";
	bool ok = true, aux = 1;
	int zi = 2;
	for (int i = 1; i <= 6; i++) {
		for (int j = 1; j <= 7; j++) {
			if (ok == 1) {
				if (j == firstday) {
					ok = 0;
					cout << " 01";
				}
				else {
					cout << "   ";
				}
			}
			else {
				
				if (zi < 10) cout << " 0" << zi;
				else cout << " " << zi;
				if (zi == zile_max) { aux = 0; break; };
				zi++;
			}
		}
		if (aux == 0) break;
		cout << "\n";
	}

}

int main(int argc, char* argv[]) {
	if (argc == 1) {
		int firstday = get_firstday();
		if (firstday == 0 || firstday == 1) firstday += 7;
		firstday -= 1;
		print_cal();
	}
	else if (argc == 2) {
		cout << "Enter year, too!";
		return 0;
	}
	else {
		if (atoi(argv[1]) < 1 || atoi(argv[1]) > 12) {
			cout << "Enter month between 1 and 12!";
			return 0;
		}
		if (atoi(argv[2]) < 1 || atoi(argv[2]) > 5000) {
			cout << "Enter year between 1 and 5000!";
			return 0;
		}
		int firstday = get_firstday(atoi(argv[1]), atoi(argv[2]));
		if (firstday == 0 || firstday == 1) firstday += 7;
		firstday -= 1;
		print_cal(atoi(argv[1]), atoi(argv[2]), firstday);
	}
	return 0;
}