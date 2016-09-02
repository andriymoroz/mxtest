#include <stdio.h>
#include <stdlib.h>

char *ones[] = {"", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
char *tens[] = {"", "", "twenty", "thirty", "fourty", "fifty", "sixty", "seventy", "eighty", "ninty"};
char *tenx[] = {"ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "ninteen"};

#define MAX_LEN_WITHIN_THOUSAND 100
#define MAX_LEN 1000

char *util(u_int64_t num)
{
    char *buf = (char *)calloc(MAX_LEN_WITHIN_THOUSAND, sizeof(char));

    int h = num / 100;
    int t = (num / 10) % 10;
    int o = num % 10;
    int skip_o = 0;

    if(h > 0)
        sprintf(buf, "%s hundred", ones[h]);
    switch(t) {
    case 0:
        break;
    case 1:
        skip_o = 1;
        sprintf(buf, "%s %s", buf, tenx[o]);
        break;
    default:
        sprintf(buf, "%s %s", buf, tens[t]);
        break;
    }
    if(o > 0 && !skip_o)
        sprintf(buf, "%s %s", buf, ones[o]);

    return buf;
}

char *units[] = {
    "thousand",
    "million",
    "billion",
    NULL
};

char *_int2string(int level, u_int64_t num)
{
    char *buf = (char *) calloc(MAX_LEN, sizeof(char));

    if (num < 1000) {
        return util(num);
    } else {
        char *phead = _int2string(level+1, num / 1000);
        char *putil = util(num % 1000);
        char *punits = (units[level])? units[level] : "(error)";

        sprintf(buf, "%s %s %s", phead, punits, putil);
        free(phead);
        free(putil);

        return buf;
    }
}

char *int2string(u_int64_t num)
{
    return _int2string(0, num);
}

#include <inttypes.h>
u_int64_t atoi64(const char *s) {
  u_int64_t i;
  char c ;
  int scanned = sscanf(s, "%" SCNu64 "%c", &i, &c);
  if (scanned >= 1)
      return i;

  return 0;
}

int main(int argc, const char *argv[])
{
    //char *number = int2string(1987555231);
    if (argc > 1) {
        char *number = int2string(atoi64(argv[1]));
        printf("%s\n", number);
        free(number);
    }

    return 0;
}

