int main() {
	time_t t;
	struct tm *p;
	char s[80];
	char *format = "%A %B %Y"; // Saturday April 2019
	t = time(NULL);
	p = gmtime(&t);
	strftime(s,80,format,p);
	printf("Time: %s", s);
	return 0;
}
