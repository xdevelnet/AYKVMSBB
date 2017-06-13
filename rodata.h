#ifndef AYKVMSBB_DBA_H
#define AYKVMSBB_DBA_H

// Generic defines

#define LOCALE_DETECT_ENV_VAR "LC_MONETARY"
#define HTTP_PORT 80

// String replacers/search patterns

#define CURRENCY_IN_POST_REQUEST_FORMAT "CURRENCYCURRENCYFMT"
#define YEAR_IN_POST_REQUEST_FORMAT "YEARINPOSTREQUESTFORMAT"
#define MONTH_IN_POST_REQUEST_FORMAT "MONTHINPOSTREQUESTFORMAT"
#define DAY_IN_POST_REQUEST_FORMAT "DAYINPOSTREQUESTFORMAT"

// The actual db! If you wish to add new record to database, you need to add lines below, edit them, and then add
// new record to currency_db structure.

// // The official name of main bank of country
// const char country_url_formatted[] = "http://your_bank_website.domain/currency_api.cgi";
// const char country_locale[] = "language_COUNTRY";
// const char country_section_ending[] = "</Appropriate_xml_section_ending_tag_from_api>";
// const char country_nominal[] = "<After_this_tag_should_be_amount_of_currency>";
// const char country_currency_chars[] = "<ISO_currency_characters>";
// const char country_currency_value[] = "<The_actual_float_point_value_what_we_are_looking_for>";

// Central Bank of Russia
const char russia_url_formatted[] = "http://www.cbr.ru/scripts/XML_daily_eng.asp?date_req=" DAY_IN_POST_REQUEST_FORMAT
	"/" MONTH_IN_POST_REQUEST_FORMAT "/" YEAR_IN_POST_REQUEST_FORMAT;
const char russia_locale[] = "ru_RU";
const char russia_section_ending[] = "</Valute>";
const char russia_nominal[] = "<Nominal>";
const char russia_currency_chars[] = "<CharCode>";
const char russia_currency_value[] = "<Value>";

// National Bank of Ukraine
const char ukraine_url_formatted[] = "http://bank.gov.ua/NBUStatService/v1/statdirectory/exchange?valcode="
	CURRENCY_IN_POST_REQUEST_FORMAT "&date=" YEAR_IN_POST_REQUEST_FORMAT MONTH_IN_POST_REQUEST_FORMAT DAY_IN_POST_REQUEST_FORMAT;
const char ukraine_locale[] = "uk_UA";
const char ukraine_section_ending[] = "</currency>";
const char ukraine_nominal[] = "";
const char ukraine_currency_chars[] = "<cc>";
const char ukraine_currency_value[] = "<rate>";

const struct {
	const char *url;            size_t url_len;
	const char *locale;         size_t locale_len;
	const char *section_end;    size_t section_end_len;
	const char *nominal;        size_t nominal_len;
	const char *currency_chars; size_t currency_chars_len;
	const char *currency_value; size_t currency_value_len;
	const char *default_currency;
} currency_db [] = {
	{
		.url = russia_url_formatted, .url_len = strizeof(russia_url_formatted),
		.locale = russia_locale, .locale_len = strizeof(russia_locale),
		.section_end = russia_section_ending, .section_end_len = strizeof(russia_section_ending),
		.nominal = russia_nominal, .nominal_len = strizeof(russia_nominal),
		.currency_chars = russia_currency_chars, .currency_chars_len = strizeof(russia_currency_chars),
		.currency_value = russia_currency_value, .currency_value_len = strizeof(russia_currency_value),
		.default_currency = "USD"
	},
	{
		.url = ukraine_url_formatted, .url_len = strizeof(ukraine_url_formatted),
		.locale = ukraine_locale, .locale_len = strizeof(ukraine_locale),
		.section_end = ukraine_section_ending, .section_end_len = strizeof(ukraine_section_ending),
		.nominal = ukraine_nominal, .nominal_len = strizeof(ukraine_nominal),
		.currency_chars = ukraine_currency_chars, .currency_chars_len = strizeof(ukraine_currency_chars),
		.currency_value = ukraine_currency_value, .currency_value_len = strizeof(ukraine_currency_value),
		.default_currency = "USD"
	},
	{.url = NULL} // the only way to detect last array element. I DARE YOU TO TOUCH THAT EVER ONCE.
};

// CURRENCIES ISO

const char *const currencies[] = { // const... const... CONSTANT POINTERS, FATASSES!
	"AZN",
	"GBP",
	"AMD",
	"BYN",
	"GEL",
	"EUR",
	"KZT",
	"KRW",
	"KGS",
	"LVL",
	"MDL",
	"RUB",
	"USD",
	"TJS",
	"TMM",
	"UZS",
	"UAH", // Ukrainian hryvnia
	"JPY", // Japanese yen
	"CNY",
    NULL
}; // I'm tired with adding currencies. Please PR me with full list and additional comments like at "UAH" and "JPY" above

// ERRORS!

#define ERR_NO_APPROPRIATE_ENV_VAR LOCALE_DETECT_ENV_VAR " environment variable should be set to let this program know your country."
#define ERR_NO_COUNTRY_IMPLEMENTED "Unfortunately, your locale support is not available. Take a look at new program version or improve it yourself."
#define ERR_INCORRECT_DATE_FORMAT "Date format is not correct."
#define ERR_INCORRECT_CURRENCY "Currency format is not valid."
#define ERR_UNAVAILABLE_CURRENCY "Unfortunately, requested currency is not available or not exist."
#define ERR_INCORRECT_INPUT "Uncorrect input."
#define ERR_ENOMEM "Not enough available memory. Exiting..."

// HTTP

const char http_proto_in_url[] = "http://";
const char http_proto_get[] = "GET ";
const char http_proto_host[] = "Host: ";
const char http_proto_connclose[] = "Connection: close";

#endif //AYKVMSBB_DBA_H
