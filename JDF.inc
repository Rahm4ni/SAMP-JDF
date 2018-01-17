/*
 *		            JDF INCLUDE v1.2
 *		 (c) Copyright 2012-2017 by Shyn Rhm
 *
 * @author: 		Shayan Rahmani & Roozbeh Baabakaan
 * @date: 		20th Dec 2012
 * @update: 		17th Jan 2018
 * @method:		jalali(g_y, g_m, g_d, &j_y, &j_m, &j_d)		Convert Gregorian date to Jalali date 
 * @method:		gregorian(j_y, j_m, j_d, &g_y, &g_m, &g_d)	Convert Jalali date to Gregorian date 
 * @method:		jdate(year, month, day)				Current Jalali date
 * @method:		jtimestamp()					Current Jalali date time stamp
 *
 * It's released under the terms of GNU GENERAL PUBLIC LICENSE v3.
 *
*/

new const g_days_in_month[12 char] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
j_days_in_month[12 char] = {31, 31, 31, 31, 31, 31, 30, 30, 30, 30, 30, 29};

jalali(g_y, g_m, g_d, &j_y, &j_m, &j_d)
{
	new g_day_no, j_day_no, j_np, jy, jm, jd, gy, gm, gd, i;
	gy = g_y - 1600;
	gm = g_m - 1;
	gd = g_d - 1;
	g_day_no = 365 * gy + ((gy + 3) / 4) - ((gy + 99) / 100) + ((gy + 399) / 400);
	for(i = 0; i < gm; i++) g_day_no += g_days_in_month[i];
	if(gm > 1 && ((gy %4 == 0 && gy %100 !=0) || (gy %400 == 0))) g_day_no++;
	g_day_no += gd;
	j_day_no = g_day_no-79;
	j_np = j_day_no / 12053; // 12053 = 365*33 + 32/4
	j_day_no = j_day_no % 12053;
	jy = 979 + 33 * j_np + 4 * (j_day_no / 1461); // 1461 = 365*4 + 4/4
	j_day_no %= 1461;
	if(j_day_no >= 366)
	{
		jy += ((j_day_no - 1) / 365);
		j_day_no = (j_day_no - 1) % 365;
	}
	for (i = 0; i < 11 && j_day_no >= j_days_in_month[i]; i++) j_day_no -= j_days_in_month[i];
	jm = i + 1;
	jd = j_day_no + 1;
	j_y = jy;
	j_m = jm;
	j_d = jd;
	return true;
}

gregorian(j_y, j_m, j_d, &g_y, &g_m, &g_d) 
{ 
	new jy, jm, jd, j_day_no, gy, g_day_no, leap, gm, gd, i;
	jy = j_y - 979;
	jm = j_m - 1;
	jd = j_d - 1;
	j_day_no = 365 * jy + (jy / 33) * 8 + (((jy %33) + 3) / 4); 
	for(i = 0; i < jm; i++) j_day_no += j_days_in_month[i]; 
	j_day_no += jd; 
	g_day_no = j_day_no + 79; 
	gy = 1600 + 400 * (g_day_no / 146097); // 146097 = 365*400 + 400/4 - 400/100 + 400/400
	g_day_no = g_day_no % 146097; 
	leap = true; 
	if(g_day_no >= 36525) // 36525 = 365*100 + 100/4 
	{ 
		g_day_no--; 
		gy += 100 * (g_day_no / 36524); // 36524 = 365*100 + 100/4 - 100/100 
		g_day_no = g_day_no % 36524; 
 
		if (g_day_no >= 365) g_day_no++; 
		else leap = false; 
	} 
	gy += 4 * (g_day_no / 1461); // 1461 = 365*4 + 4/4
	g_day_no %= 1461; 
	if(g_day_no >= 366)
	{ 
		leap = false; 
		g_day_no--; 
		gy += (g_day_no / 365); 
		g_day_no = g_day_no % 365; 
	} 
	for (i = 0; g_day_no >= g_days_in_month[i] + (i == 1 && leap); i++) g_day_no -= g_days_in_month[i] + (i == 1 && leap); 
	gm = i + 1; 
	gd = g_day_no + 1; 
	g_y = gy;
	g_m = gm;
	g_d = gd;
	return true;
} 

jdate(&y, &m, &d) {
	new yy, mm, dd;
	getdate(yy, mm, dd);
	jalali(yy, mm, dd, y, m, d);
	return true;
}

jtimestamp() {
	new str[20], d[3], o[3], t[3];
	getdate(o[0], o[1], o[2]);
	jalali(o[0], o[1], o[2], d[0], d[1], d[2]);
	gettime(t[0], t[1], t[2]);
	
	format(str, sizeof(str), "%d-%02d-%02d %02d:%02d:%02d", d[0], d[1], d[2], t[0], t[1], t[2]);
	return str;
}
