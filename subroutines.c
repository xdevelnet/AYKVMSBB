#ifndef AYKVMSBB_CURRENCIES_ROUTINES_H
#define AYKVMSBB_CURRENCIES_ROUTINES_H

bool check_if_locale_available_and_choose_db_entry(const char *locale, size_t *entry) {
	size_t iterator = 0;
	while (forever) {
		if (currency_db[iterator].url == NULL) return false;
		if (stralmosteq(locale, currency_db[iterator].locale, currency_db[iterator].locale_len)) break;
		iterator++;
	}
	*entry = iterator;
	return true;
}

static inline void day_from_previous_month_please(int day) {
	if (required_data.month == 1) {
		required_data.month = 12;
		required_data.year--;
	} else required_data.month--;
	required_data.day = day;
}

static inline void set_date(const char *str) {
	size_t len = strlen(str);
	if (len > 8 or (len < 7 and len > 4)) fall(ERR_INCORRECT_DATE_FORMAT); // http://e.lvme.me/rkozb5.jpg
	if (len < 3) { // 12 or 8
		int req = atoi(str);
		if (req > required_data.day) day_from_previous_month_please(req); else required_data.day = req;
		return;
	}
	char buffer[3] = {'\0', '\0', '\0'};
	if (len < 5) { // 501 or 3006
		if (str[len - 2] == '0') required_data.month = atoi(str + len - 1); else required_data.month = atoi(str + len - 2);
		if (len == 3) memcpy(buffer, str, 1); else memcpy(buffer, str, 2);
		required_data.day = atoi(buffer);
		return;
	}
	required_data.year = atoi(str + len - 4); // 2022014 or 12051999
	if (str[len - 6] == '0') memcpy(buffer, str + len - 5, 1); else memcpy(buffer, str + len - 6, 2);
	required_data.month = atoi(buffer);
	if (len == 8) memcpy(buffer, str, 2); else {
		memcpy(buffer, str, 1);
		buffer[1] = '\0';
	}
	required_data.day = atoi(buffer);
}

static inline void check_date() {
	if (required_data.month > 12) fall(ERR_INCORRECT_DATE_FORMAT);
	if (required_data.day > 31) fall(ERR_INCORRECT_DATE_FORMAT);
}

static inline bool check_currency_existence(const char *currency) {
	size_t iterator = 0;
	while (forever) {
		if (currencies[iterator] == NULL) return false;
		if (streq(currencies[iterator], currency)) break;
		iterator++;
	}
	return true;
}

static inline void check_and_set_currency(char *str) {
	size_t len = strlen(str);
	if (len > 3 or len < 3 or str[0] < 'A' or str[1] < 'A' or str[2] < 'A' or
		str[0] > 'z' or str[1] > 'z' or str[2] > 'z') fall(ERR_INCORRECT_CURRENCY);
	str[0] = (char) toupper(str[0]); // Why the hell these functions are operating with int values? I really wanna reinvent them all!
	str[1] = (char) toupper(str[1]); // Reinventing the whell... mmmm... delicious... can't resist anymooooreeee...
	str[2] = (char) toupper(str[2]);

	if (check_currency_existence(str) == false) fall(ERR_UNAVAILABLE_CURRENCY);
	required_data.requested_currency = str;
}

static inline void parse_cmd(int argc, char * const * const argv) {
	if (argc <= 1) {
		required_data.requested_currency = currency_db[required_data.db_entry].default_currency;
		return;
	}
	if (streq(argv[1], "?") or streq(argv[1], "--help") or streq(argv[1], "-h")) print_help_and_exit();

	if (argc == 2) {
		if (isdigit(argv[1][0])) {
			set_date(argv[1]);
			check_date();
			required_data.requested_currency = currency_db[required_data.db_entry].default_currency;
			return;
		}
		if (isalpha(argv[1][0])) {
			check_and_set_currency(argv[1]);
			return;
		} else fall(ERR_INCORRECT_INPUT);
	}

	if (argc == 3) {
		if ( !((isdigit(argv[1][0]) or isdigit(argv[2][0])) and (isalpha(argv[1][0]) or isalpha(argv[2][0])))) fall(ERR_INCORRECT_INPUT);
		// can someone help me with rewriting this huge logical expresion above? That's too complicated! (actually I'm lazy noob)
		if (isdigit(argv[1][0])) {
			set_date(argv[1]);
			check_date();
			check_and_set_currency(argv[2]);
		} else {
			set_date(argv[2]);
			check_date();
			check_and_set_currency(argv[1]);
		}
	}
}

static inline void collect_and_check_data() {
	required_data.currency_locale = getenv(LOCALE_DETECT_ENV_VAR);
	if (required_data.currency_locale == NULL) fall(ERR_NO_APPROPRIATE_ENV_VAR);
	if (check_if_locale_available_and_choose_db_entry(required_data.currency_locale, &required_data.db_entry) == false) fall(ERR_NO_COUNTRY_IMPLEMENTED);

	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	required_data.year = tm.tm_year + 1900;
	required_data.month = tm.tm_mon + 1;
	required_data.day = tm.tm_mday;
}

// http stuff

static inline void chop_chop_hostname_from_url(const char *url, char *buffer_to_fill_in) {
	if (stralmosteq(url, http_proto_in_url, strizeof(http_proto_in_url))) url += strizeof(http_proto_in_url);
	memcpy(buffer_to_fill_in, url, strchr(url, '/') - url);
}

static inline void compose_http_request(char *buffer, const char *host, const char *url) {
	sprintf(buffer, "%s%s\n%s%s\n%s\n\n", http_proto_get, strstr(url, host) + strlen(host), http_proto_host, host, http_proto_connclose);

	strreplace_dumb(buffer, CURRENCY_IN_POST_REQUEST_FORMAT, required_data.requested_currency);
	char dates[5]; // should be enough for every part of date. E.g. 1999 or 12
	sprintf(dates, "%d", required_data.year);
	strreplace_dumb(buffer, YEAR_IN_POST_REQUEST_FORMAT, dates);
	sprintf(dates, "%02d", required_data.month);
	strreplace_dumb(buffer, MONTH_IN_POST_REQUEST_FORMAT, dates);
	sprintf(dates, "%02d", required_data.day);
	strreplace_dumb(buffer, DAY_IN_POST_REQUEST_FORMAT, dates);
}

// networKING starts here

bool socket_data_retreiver(int fd, char *buffer, size_t amount) { // Ranwe ya dumal 4to odnogo read() hvatit na vse. No socket-i eto vam ne wutki!
	struct pollfd pollfds[1] = {{ .fd = fd, .events = POLLIN | POLLPRI }};
	ssize_t got = -1;
	amount--;
	while (forever) {
		if (poll(pollfds, 1, 10000) < 0) return false;
		got = read(fd, buffer, amount);
		if (got < 0) return false;
		if (got == 0) break; // Teper' moi volosi myagkie i welkovistie!
		buffer += got;
		amount -= got;
	}
	*buffer = '\0';
	return true;
}

struct netbuffer_t {
	char b[24576]; // should be enough, right?..
};

static inline char *http_action() {
	char *netbuffer = calloc(sizeof(struct netbuffer_t), sizeof(char));
	if (netbuffer == NULL) fall(ERR_ENOMEM);
	chop_chop_hostname_from_url(currency_db[required_data.db_entry].url, netbuffer);
	struct hostent *myhost = gethostbyname(netbuffer);
	if (myhost == NULL) fall(hstrerror(h_errno));
	struct sockaddr_in connaddr = {.sin_family = AF_INET, .sin_port = CT_HTONS(HTTP_PORT), .sin_addr.s_addr = ((struct in_addr *)myhost->h_addr_list[0])->s_addr};
	int fd;
	if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0 or connect(fd, (const struct sockaddr *) &connaddr, sizeof(struct sockaddr_in)) < 0
		) fall((free(netbuffer), strerror(errno))); // https://media.giphy.com/media/12NOkUXx8ffFBK/giphy.gif
	compose_http_request(netbuffer, myhost->h_name, currency_db[required_data.db_entry].url);
	unsigned short int attempts = 0;
	ssize_t got = -1;
	while (attempts++ < 5) {
		got = write(fd, netbuffer, strlen(netbuffer));
		if (got > 0) break;
	}
	if (got < 0) {
		free(netbuffer);
		fall(strerror(errno));
	}

	if (socket_data_retreiver(fd, netbuffer, sizeof(struct netbuffer_t)) != true) {
		free(netbuffer);
		fall(strerror(errno));
	}
	close(fd);

	return netbuffer;
}

int compose_and_print_result(double value, double nominal) {
	if (value == 0) return EXIT_FAILURE;
	char valbuffer[15];
	char nombuffer[15];

	snprintf(valbuffer, sizeof(valbuffer), "%f", value);
	backward_zero_eater(valbuffer);
	printf("%s: %s\n", required_data.requested_currency, valbuffer);
	if (nominal != 1) {
		snprintf(nombuffer, sizeof(nombuffer), "%f", nominal);
		backward_zero_eater(nombuffer);
		printf("for %s amount.\n", nombuffer);
	}
	return EXIT_SUCCESS;
}

#endif //AYKVMSBB_CURRENCIES_ROUTINES_H
