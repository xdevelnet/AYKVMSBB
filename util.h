#ifndef AYKVMSBB_UTIL_H
#define AYKVMSBB_UTIL_H

#define strizeof(a) (sizeof(a)-1)
#define eprintf(...) fprintf (stderr, __VA_ARGS__)
#define forever true
#define streq(s1, s2) (strcmp((s1), (s2)) == 0)
#define stralmosteq(s1, s2, size) (strncmp((s1), (s2), (size)) == 0)
#define CT_HTONS(x) (((x >> 8) & 0x00FF) | ((x << 8) & 0xFF00))

int fall(const char *error) {
	eprintf("%s\n", error);
	exit(EXIT_FAILURE);
}

void print_help_and_exit() {
	eprintf("Usage:\n");
	exit(EXIT_SUCCESS);
}

bool strreplace_dumb(char *string, const char *search, const char *replacer) { // replace part of the string, but replacer should not be bigger then search
	size_t searchlen = strlen(search);
	size_t replacerlen = strlen(replacer);
	size_t stringlen = strlen(string);
	if (replacerlen > searchlen or string == NULL or string[0] == '\0') return false;
	char *s = strstr(string, search);
	if (s == NULL) return false;
	memcpy(s, replacer, replacerlen); // https://imgflip.com/s/meme/Futurama-Fry.jpg
	if (searchlen != replacerlen ) memmove(s + replacerlen, s + searchlen, stringlen - (s + searchlen - string) + 1);
	return true;
}

double unsafe_numeric_eater(char *str) {
	size_t position = 0;
	while (str[position] != '\0') {
		if (isdigit(str[position])) {position++; continue;}
		if (str[position] == ',') str[position] = '.';
		break;
	}
	return strtod(str, NULL);
}

// becuase I'm already engaged with reinventing everything! Well, ughh, also because I don't want any kind of dependencies.
double xml_currency_parser(char *str,
                           const char *sectend, size_t sectend_len,
                           const char *nominal, size_t nominal_len,
                           const char *currency_chars, size_t currency_chars_len,
                           const char *currency_rate, size_t currency_rate_len,
                           double *nominalval) {
	double value = 0;
	char *current_valute_tag;
	char *current_currency_chars_tag;
	char *current_nominal_tag = NULL; // https://imgflip.com/s/meme/One-Does-Not-Simply.jpg
	char *current_currency_tag;
	if (sectend_len == 0) return 0;
	while (forever) {
		current_valute_tag = strstr(str, sectend);
		if (current_valute_tag == NULL) break;
		current_valute_tag[0] = '\0';
		current_currency_chars_tag = strstr(str, currency_chars);
		if (current_currency_chars_tag == NULL) break;
		if (stralmosteq(current_currency_chars_tag + currency_chars_len, required_data.requested_currency, 3)) {
			current_currency_tag = strstr(str, currency_rate);
			if (current_currency_tag == NULL) break;
			value = unsafe_numeric_eater(current_currency_tag + currency_rate_len);
			if (nominal[0] != '\0') current_nominal_tag = strstr(str, nominal);
			if (current_nominal_tag != NULL) *nominalval = unsafe_numeric_eater(current_nominal_tag + nominal_len);
			break;
		}
		str = current_valute_tag + 1;
	}
	if (value == 0) eprintf("%s\n", "No valid information available.");
	return value;
}

void backward_zero_eater(char *str) { // removes all trailing zeroes
	str = strchr(str, '.');
	if (str == NULL) return;
	str++;
	size_t fraction = strlen(str) - 1;
	while (forever) {
		if (str[fraction] == '0') str[fraction] = '\0'; else break; // http://1001gag.com/content/uploads/images/December2015/semicolon.jpg
		fraction--;
	}
	if (str[fraction] == '.') str[fraction] = '\0';
}

#endif //AYKVMSBB_UTIL_H
