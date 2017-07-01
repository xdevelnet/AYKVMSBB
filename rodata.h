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
	"AFN", // Afghani
	"EUR", // Euro
	"ALL", // Lek
	"DZD", // Algerian Dinar
	"USD", // US Dollar
	"EUR", // Euro
	"AOA", // Kwanza
	"XCD", // East Caribbean Dollar
	"XCD", // East Caribbean Dollar
	"ARS", // Argentine Peso
	"AMD", // Armenian Dram
	"AWG", // Aruban Florin
	"AUD", // Australian Dollar
	"EUR", // Euro
	"AZN", // Azerbaijan Manat
	"BSD", // Bahamian Dollar
	"BHD", // Bahraini Dinar
	"BDT", // Taka
	"BBD", // Barbados Dollar
	"BYN", // Belarusian Ruble
	"EUR", // Euro
	"BZD", // Belize Dollar
	"XOF", // CFA Franc BCEAO
	"BMD", // Bermudian Dollar
	"INR", // Indian Rupee
	"BTN", // Ngultrum
	"BOB", // Boliviano
	"BOV", // Mvdol
	"USD", // US Dollar
	"BAM", // Convertible Mark
	"BWP", // Pula
	"NOK", // Norwegian Krone
	"BRL", // Brazilian Real
	"USD", // US Dollar
	"BND", // Brunei Dollar
	"BGN", // Bulgarian Lev
	"XOF", // CFA Franc BCEAO
	"BIF", // Burundi Franc
	"CVE", // Cabo Verde Escudo
	"KHR", // Riel
	"XAF", // CFA Franc BEAC
	"CAD", // Canadian Dollar
	"KYD", // Cayman Islands Dollar
	"XAF", // CFA Franc BEAC
	"XAF", // CFA Franc BEAC
	"CLP", // Chilean Peso
	"CLF", // Unidad de Fomento
	"CNY", // Yuan Renminbi
	"AUD", // Australian Dollar
	"AUD", // Australian Dollar
	"COP", // Colombian Peso
	"COU", // Unidad de Valor Real
	"KMF", // Comorian Franc 
	"CDF", // Congolese Franc
	"XAF", // CFA Franc BEAC
	"NZD", // New Zealand Dollar
	"CRC", // Costa Rican Colon
	"XOF", // CFA Franc BCEAO
	"HRK", // Kuna
	"CUP", // Cuban Peso
	"CUC", // Peso Convertible
	"ANG", // Netherlands Antillean Guilder
	"EUR", // Euro
	"CZK", // Czech Koruna
	"DKK", // Danish Krone
	"DJF", // Djibouti Franc
	"XCD", // East Caribbean Dollar
	"DOP", // Dominican Peso
	"USD", // US Dollar
	"EGP", // Egyptian Pound
	"SVC", // El Salvador Colon
	"USD", // US Dollar
	"XAF", // CFA Franc BEAC
	"ERN", // Nakfa
	"EUR", // Euro
	"ETB", // Ethiopian Birr
	"EUR", // Euro
	"FKP", // Falkland Islands Pound
	"DKK", // Danish Krone
	"FJD", // Fiji Dollar
	"EUR", // Euro
	"EUR", // Euro
	"EUR", // Euro
	"XPF", // CFP Franc
	"EUR", // Euro
	"XAF", // CFA Franc BEAC
	"GMD", // Dalasi
	"GEL", // Lari
	"EUR", // Euro
	"GHS", // Ghana Cedi
	"GIP", // Gibraltar Pound
	"EUR", // Euro
	"DKK", // Danish Krone
	"XCD", // East Caribbean Dollar
	"EUR", // Euro
	"USD", // US Dollar
	"GTQ", // Quetzal
	"GBP", // Pound Sterling
	"GNF", // Guinean Franc
	"XOF", // CFA Franc BCEAO
	"GYD", // Guyana Dollar
	"HTG", // Gourde
	"USD", // US Dollar
	"AUD", // Australian Dollar
	"EUR", // Euro
	"HNL", // Lempira
	"HKD", // Hong Kong Dollar
	"HUF", // Forint
	"ISK", // Iceland Krona
	"INR", // Indian Rupee
	"IDR", // Rupiah
	"XDR", // SDR (Special Drawing Right)
	"IRR", // Iranian Rial
	"IQD", // Iraqi Dinar
	"EUR", // Euro
	"GBP", // Pound Sterling
	"ILS", // New Israeli Sheqel
	"EUR", // Euro
	"JMD", // Jamaican Dollar
	"JPY", // Yen
	"GBP", // Pound Sterling
	"JOD", // Jordanian Dinar
	"KZT", // Tenge
	"KES", // Kenyan Shilling
	"AUD", // Australian Dollar
	"KPW", // North Korean Won
	"KRW", // Won
	"KWD", // Kuwaiti Dinar
	"KGS", // Som
	"LAK", // Lao Kip
	"EUR", // Euro
	"LBP", // Lebanese Pound
	"LSL", // Loti
	"ZAR", // Rand
	"LRD", // Liberian Dollar
	"LYD", // Libyan Dinar
	"CHF", // Swiss Franc
	"EUR", // Euro
	"EUR", // Euro
	"MOP", // Pataca
	"MKD", // Denar
	"MGA", // Malagasy Ariary
	"MWK", // Malawi Kwacha
	"MYR", // Malaysian Ringgit
	"MVR", // Rufiyaa
	"XOF", // CFA Franc BCEAO
	"EUR", // Euro
	"USD", // US Dollar
	"EUR", // Euro
	"MRO", // Ouguiya
	"MUR", // Mauritius Rupee
	"EUR", // Euro
	"XUA", // ADB Unit of Account
	"MXN", // Mexican Peso
	"MXV", // Mexican Unidad de Inversion (UDI)
	"USD", // US Dollar
	"MDL", // Moldovan Leu
	"EUR", // Euro
	"MNT", // Tugrik
	"EUR", // Euro
	"XCD", // East Caribbean Dollar
	"MAD", // Moroccan Dirham
	"MZN", // Mozambique Metical
	"MMK", // Kyat
	"NAD", // Namibia Dollar
	"ZAR", // Rand
	"AUD", // Australian Dollar
	"NPR", // Nepalese Rupee
	"EUR", // Euro
	"XPF", // CFP Franc
	"NZD", // New Zealand Dollar
	"NIO", // Cordoba Oro
	"XOF", // CFA Franc BCEAO
	"NGN", // Naira
	"NZD", // New Zealand Dollar
	"AUD", // Australian Dollar
	"USD", // US Dollar
	"NOK", // Norwegian Krone
	"OMR", // Rial Omani
	"PKR", // Pakistan Rupee
	"USD", // US Dollar
	"PAB", // Balboa
	"USD", // US Dollar
	"PGK", // Kina
	"PYG", // Guarani
	"PEN", // Sol
	"PHP", // Philippine Peso
	"NZD", // New Zealand Dollar
	"PLN", // Zloty
	"EUR", // Euro
	"USD", // US Dollar
	"QAR", // Qatari Rial
	"EUR", // Euro
	"RON", // Romanian Leu
	"RUB", // Russian Ruble
	"RWF", // Rwanda Franc
	"EUR", // Euro
	"SHP", // Saint Helena Pound
	"XCD", // East Caribbean Dollar
	"XCD", // East Caribbean Dollar
	"EUR", // Euro
	"EUR", // Euro
	"XCD", // East Caribbean Dollar
	"WST", // Tala
	"EUR", // Euro
	"STD", // Dobra
	"SAR", // Saudi Riyal
	"XOF", // CFA Franc BCEAO
	"RSD", // Serbian Dinar
	"SCR", // Seychelles Rupee
	"SLL", // Leone
	"SGD", // Singapore Dollar
	"ANG", // Netherlands Antillean Guilder
	"XSU", // Sucre
	"EUR", // Euro
	"EUR", // Euro
	"SBD", // Solomon Islands Dollar
	"SOS", // Somali Shilling
	"ZAR", // Rand
	"SSP", // South Sudanese Pound
	"EUR", // Euro
	"LKR", // Sri Lanka Rupee
	"SDG", // Sudanese Pound
	"SRD", // Surinam Dollar
	"NOK", // Norwegian Krone
	"SZL", // Lilangeni
	"SEK", // Swedish Krona
	"CHF", // Swiss Franc
	"CHE", // WIR Euro
	"CHW", // WIR Franc
	"SYP", // Syrian Pound
	"TWD", // New Taiwan Dollar
	"TJS", // Somoni
	"TZS", // Tanzanian Shilling
	"THB", // Baht
	"USD", // US Dollar
	"XOF", // CFA Franc BCEAO
	"NZD", // New Zealand Dollar
	"TOP", // Pa’anga
	"TTD", // Trinidad and Tobago Dollar
	"TND", // Tunisian Dinar
	"TRY", // Turkish Lira
	"TMT", // Turkmenistan New Manat
	"USD", // US Dollar
	"AUD", // Australian Dollar
	"UGX", // Uganda Shilling
	"UAH", // Hryvnia
	"AED", // UAE Dirham
	"GBP", // Pound Sterling
	"USD", // US Dollar
	"USD", // US Dollar
	"USN", // US Dollar (Next day)
	"UYU", // Peso Uruguayo
	"UYI", // Uruguay Peso en Unidades Indexadas (URUIURUI)
	"UZS", // Uzbekistan Sum
	"VUV", // Vatu
	"VEF", // Bolívar
	"VND", // Dong
	"USD", // US Dollar
	"USD", // US Dollar
	"XPF", // CFP Franc
	"MAD", // Moroccan Dirham
	"YER", // Yemeni Rial
	"ZMW", // Zambian Kwacha
	"ZWL", // Zimbabwe Dollar
	"XBA", // Bond Markets Unit European Composite Unit (EURCO)
	"XBB", // Bond Markets Unit European Monetary Unit (E.M.U.-6)
	"XBC", // Bond Markets Unit European Unit of Account 9 (E.U.A.-9)
	"XBD", // Bond Markets Unit European Unit of Account 17 (E.U.A.-17)
	"XTS", // Codes specifically reserved for testing purposes
	"XAU", // Gold
	"XPD", // Palladium
	"XPT", // Platinum
	"XAG", // Silver
    NULL
};

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
