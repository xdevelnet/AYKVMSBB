#define _BSD_SOURCE // 0nly 4 hstrerror()

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>
#include <iso646.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>
#include <poll.h>

struct {
	const char *currency_locale;
	const char *requested_currency;
	int year;
	int month;
	int day;
	size_t db_entry;
} required_data;

#include "util.h"
#include "rodata.h"
#include "subroutines.h"

int main(int argc, char **argv) {
	collect_and_check_data();
	parse_cmd(argc, argv);
	char *retreived_data = http_action();
	double nominal = 1;
	double result = xml_currency_parser(retreived_data,
	                                   currency_db[required_data.db_entry].section_end, currency_db[required_data.db_entry].section_end_len,
	                                   currency_db[required_data.db_entry].nominal, currency_db[required_data.db_entry].nominal_len,
	                                   currency_db[required_data.db_entry].currency_chars, currency_db[required_data.db_entry].currency_chars_len,
	                                   currency_db[required_data.db_entry].currency_value, currency_db[required_data.db_entry].currency_value_len,
	                                   &nominal);
	free(retreived_data);
	return compose_and_print_result(result, nominal);
}