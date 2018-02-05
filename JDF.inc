/*
 *		            JDF INCLUDE v1.3
 *		 (c) Copyright 2012-2017 by Shyn Rhm
 *
 * @author: 		Shayan Rahmani & Roozbeh Baabakaan
 * @date: 		20th Dec 2012
 * @update: 		17th Jan 2018
 *
 * It's released under the terms of GNU GENERAL PUBLIC LICENSE v3.
 *
 * @method:		Jalali(g_y, g_m, g_d, &j_y, &j_m, &j_d) »» Convert Gregorian date to Jalali date 
 * @method:		Gregorian(j_y, j_m, j_d, &g_y, &g_m, &g_d) »» Convert Jalali date to Gregorian date 
 * @method:		JDate(year, month, day)	»» Current Jalali date
 * @method:		JDatestamp() »» Current Jalali datestamp
 * @method:		TimestampToJDate(Timestamp, &year, &month, &day, &hour, &minute, &second, HourGMT = 3, MinuteGMT = 30) »» Convert Gregorian timestamp to Jalali date
 * @method:		JDateToTimestamp(year, month, day) »» Convert Jalali date to Gregorian timestamp
 * @method:		ReturnJDate(timestamp) »» Return Jalali date from timestamp
 *
 * @preprocessor: define AfghanistanMonths »» Use this when you wanna use Afghanistan months names
*/

new const GregorianTimes[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
JalaliTimes[12] = { 31, 31, 31, 31, 31, 31, 30, 30, 30, 30, 30, 29 },
MonthTimes[12][4] =
{
        { 31, 31, 2678400, 2678400 },
        { 28, 29, 2419200, 2505600 },
        { 31, 31, 2678400, 2678400 },
        { 30, 30, 2592000, 2592000 },
        { 31, 31, 2678400, 2678400 },
        { 30, 30, 2592000, 2592000 },
        { 31, 31, 2678400, 2678400 },
        { 31, 31, 2678400, 2678400 },
        { 30, 30, 2592000, 2592000 },
        { 31, 31, 2678400, 2678400 },
        { 30, 30, 2592000, 2592000 },
        { 31, 31, 2678400, 2678400 }
};

stock IsLeapYear(year)
{
        if(year % 4 == 0) return 1;
        else return 0;
}

stock Jalali(g_y, g_m, g_d, &j_y, &j_m, &j_d)
{
	new g_day_no, j_day_no, j_np, jy, jm, jd, gy, gm, gd, i;
	gy = g_y - 1600;
	gm = g_m - 1;
	gd = g_d - 1;
	g_day_no = 365 * gy + ((gy + 3) / 4) - ((gy + 99) / 100) + ((gy + 399) / 400);
	for(i = 0; i < gm; i++) g_day_no += GregorianTimes[i];
	if(gm > 1 && ((gy %4 == 0 && gy %100 !=0) || (gy %400 == 0))) g_day_no++;
	g_day_no += gd;
	j_day_no = g_day_no-79;
	j_np = j_day_no / 12053;
	j_day_no = j_day_no % 12053;
	jy = 979 + 33 * j_np + 4 * (j_day_no / 1461);
	j_day_no %= 1461;
	if(j_day_no >= 366)
	{
		jy += ((j_day_no - 1) / 365);
		j_day_no = (j_day_no - 1) % 365;
	}
	for (i = 0; i < 11 && j_day_no >= JalaliTimes[i]; i++) j_day_no -= JalaliTimes[i];
	jm = i + 1;
	jd = j_day_no + 1;
	j_y = jy;
	j_m = jm;
	j_d = jd;
	return true;
}

stock Gregorian(j_y, j_m, j_d, &g_y, &g_m, &g_d) 
{ 
	new jy, jm, jd, j_day_no, gy, g_day_no, gm, gd, i, bool: leap;
	jy = j_y - 979;
	jm = j_m - 1;
	jd = j_d - 1;
	j_day_no = 365 * jy + (jy / 33) * 8 + (((jy %33) + 3) / 4); 
	for(i = 0; i < jm; i++) j_day_no += JalaliTimes[i]; 
	j_day_no += jd; 
	g_day_no = j_day_no + 79; 
	gy = 1600 + 400 * (g_day_no / 146097);
	g_day_no = g_day_no % 146097; 
	leap = true; 
	if(g_day_no >= 36525)
	{ 
		g_day_no--; 
		gy += 100 * (g_day_no / 36524);
		g_day_no = g_day_no % 36524; 
 
		if (g_day_no >= 365) g_day_no++; 
		else leap = false; 
	} 
	gy += 4 * (g_day_no / 1461);
	g_day_no %= 1461; 
	if(g_day_no >= 366)
	{ 
		leap = false; 
		g_day_no--; 
		gy += (g_day_no / 365); 
		g_day_no = g_day_no % 365; 
	} 
	for (i = 0; g_day_no >= GregorianTimes[i] + (i == 1 && leap ? (1) : (0)); i++)
		g_day_no -= GregorianTimes[i] + (i == 1 && leap ? (1) : (0)); 
	gm = i + 1; 
	gd = g_day_no + 1; 
	g_y = gy;
	g_m = gm;
	g_d = gd;
	return true;
} 

stock JDate(&y, &m, &d)
{
	new yy, mm, dd;
	getdate(yy, mm, dd);
	Jalali(yy, mm, dd, y, m, d);
	return true;
}

stock JDatestamp()
{
	new str[20], year, month, day, hour, minute, second;
	JDate(year, month, day);
	gettime(hour, minute, second);
	
	format(str, sizeof(str), "%d-%02d-%02d %02d:%02d:%02d", year, month, day, hour, minute, second);
	return str;
}

stock TimestampToJDate(Timestamp, &year, &month, &day, &hour, &minute, &second, HourGMT = 3, MinuteGMT = 30)
{
        new tmp = 2;
        year = 1970;
        month = 1;
        Timestamp -= 172800;
        for(;;)
        {
                if(Timestamp >= 31536000)
                {
                        year ++;
                        Timestamp -= 31536000;
                        tmp ++;
                        if(tmp == 4)
                        {
                                if(Timestamp >= 31622400)
                                {
                                        tmp = 0;
                                        year ++;
                                        Timestamp -= 31622400;
                                }
                                else break;
                        }
                }
                else break;
        }              
        for(new i = 0; i < 12; i ++)
        {
                if(Timestamp >= MonthTimes[i][2 + IsLeapYear(year)])
                {
                        month ++;
                        Timestamp -= MonthTimes[i][2 + IsLeapYear(year)];
                }
                else break;
        }
        day = 1 + (Timestamp / 86400);
        Timestamp %= 86400;
        hour = HourGMT + (Timestamp / 3600);
        Timestamp %= 3600;
        minute = MinuteGMT + (Timestamp / 60);
        second = (Timestamp % 60);
        if(minute > 59)
        {
                minute = 0;
                hour ++;
        }
        if(hour > 23)
        {
                hour -= 24;
                day ++;
        }      
        if(day > MonthTimes[month][IsLeapYear(year)])
        {
                day = 1;
                month ++;
        }
        if(month > 12)
        {
                month = 1;
                year ++;
        }
        Jalali(year, month, day, year, month, day);
        return 1;
}

stock JDateToTimestamp(year, month, day)
{
	Gregorian(year, month, day, year, month, day);
    new total = 0, tmp = 0;
    total += day * 86400;
    if(month == 2 && day < 29) tmp = ((year - 1968) / 4 - 2);
    else tmp = ((year - 1968) / 4 - 1);
    total += tmp * 31622400;
    total += (year - 1970 - tmp) * 31536000;
    for(new i = 1; i < month; i ++) total += MonthTimes[i][0 + IsLeapYear(year)] * 86400;
    return total;
}

stock ReturnJDate(timestamp)
{
	new year, month, day, unused;
	TimestampToDate(timestamp, year, month, day, unused, unused, unused, 0);
	Jalali(year, month, day, year, month, day);
	static monthname[15];
	#if defined AfghanistanMonths
	switch (month)
	{
	    case 1: monthname = "Farvardin";
	    case 2: monthname = "Ordibehesht";
	    case 3: monthname = "Khordad";
	    case 4: monthname = "Tir";
	    case 5: monthname = "Mordad";
	    case 6: monthname = "Shahrivar";
	    case 7: monthname = "Mehr";
	    case 8: monthname = "Aban";
	    case 9: monthname = "Azar";
	    case 10: monthname = "Dey";
	    case 11: monthname = "Bahman";
	    case 12: monthname = "Esfand";
	}
	#else
	switch (month)
	{
	    case 1: monthname = "Hamal";
	    case 2: monthname = "Sawr";
	    case 3: monthname = "Jawza";
	    case 4: monthname = "Saratan";
	    case 5: monthname = "Asad";
	    case 6: monthname = "Sombole";
	    case 7: monthname = "Mizan";
	    case 8: monthname = "Aqrab";
	    case 9: monthname = "Qaws";
	    case 10: monthname = "Jady";
	    case 11: monthname = "Dalv";
	    case 12: monthname = "Hut";
	}
	#endif
	new date[30];
	format(date, sizeof (date), "%i %s, %i", day, monthname, year);
	return date;
}
