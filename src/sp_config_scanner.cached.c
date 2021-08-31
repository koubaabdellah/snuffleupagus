/* Generated by re2c */
#include "php_snuffleupagus.h"

enum YYCONDTYPE {
	yycinit,
	yyccond,
	yyccond_op,
	yycrule,
};


#define cs_error_log(fmt, ...) sp_log_err("config", fmt, ##__VA_ARGS__)

zend_string *sp_get_arg_string(sp_parsed_keyword *kw) {
  if (!kw || !kw->arg) {
    return NULL;
  }
  zend_string *ret = zend_string_init(kw->arg, kw->arglen, 1);
  char *pin, *pout;
  pin = pout = ZSTR_VAL(ret);
  char *pend = pin + ZSTR_LEN(ret);

  while (pin < pend) {
    if (*pin == '\\') {
      pin++;
    }
    *pout = *pin;
    pin++; pout++;
  }

  if (pin != pout) {
    size_t len = pout - ZSTR_VAL(ret);
    ret = zend_string_truncate(ret, len, 1);
    ZSTR_VAL(ret)[len] = 0;
  }

  return ret;
}

zend_string *sp_get_textual_representation(sp_parsed_keyword *parsed_rule) {
  // a rule is "sp.keyword...keyword(arg);\0"
  size_t len = 3; // sp + ;
  sp_parsed_keyword *kw;
  for (kw = parsed_rule; kw->kw; kw++) {
    len++; // .
    len += kw->kwlen;
    if (kw->argtype == SP_ARGTYPE_EMPTY) {
      len += 2; // ()
    } else if (kw->argtype == SP_ARGTYPE_STR) {
        len += 4;
        len += kw->arglen;
    }
  }
  zend_string *ret = zend_string_alloc(len, 1);
  char *ptr = ZSTR_VAL(ret);
  memcpy(ptr, "sp", 2); ptr += 2;
  for (kw = parsed_rule; kw->kw; kw++) {
    *ptr++ = '.';
    memcpy(ptr, kw->kw, kw->kwlen); ptr += kw->kwlen;
    if (kw->argtype == SP_ARGTYPE_EMPTY || kw->argtype == SP_ARGTYPE_STR || kw->argtype == SP_ARGTYPE_UNKNOWN) {
      *ptr++ = '(';
    }
    if (kw->argtype == SP_ARGTYPE_STR && kw->arg) {
      *ptr++ = '"';
      memcpy(ptr, kw->arg, kw->arglen); ptr += kw->arglen;
      *ptr++ = '"';
    }
    if (kw->argtype == SP_ARGTYPE_EMPTY || kw->argtype == SP_ARGTYPE_STR || kw->argtype == SP_ARGTYPE_UNKNOWN) {
      *ptr++ = ')';
    }
  }
  *ptr++ = ';';
  *ptr = 0;
  return ret;
}

static void str_dtor(zval *zv) {
  zend_string_release_ex(Z_STR_P(zv), 1);
}

static int apply_op(int v1, char op, int v2, int neg) {
  if (neg) { v2 = !v2; }
  switch (op) {
    case 0: return v2;
    case '&': return (v1 && v2);
    case '|': return (v1 || v2);
    case '<': return (v1 < v2);
    case '>': return (v1 > v2);
    case '=': return (v1 == v2);
  }
  return 0;
}

#define APPLY_OP(v2) cond_res = apply_op(cond_res, cond_op, v2, cond_neg); cond_op = cond_neg = 0;

zend_result sp_config_scan(char *data, zend_result (*process_rule)(sp_parsed_keyword*))
{
  const char *YYCURSOR = data;
  const char *YYMARKER, *t1, *t2, *t3, *t4;
  const char *yyt1;
const char *yyt2;
const char *yyt3;
const char *yyt4;


  int ret = FAILURE;

  const int max_keywords = 16;
  sp_parsed_keyword parsed_rule[max_keywords+1];
  int kw_i = 0;

  HashTable vars;
  zend_hash_init(&vars, 10, NULL, str_dtor, 1);

  int cond_res = 1;
  char cond_op = 0;
  int cond_neg = 0;

  int cond = yycinit;
  long lineno = 1;

  
{
	char yych;
	unsigned int yyaccept = 0;
	if (cond < 2) {
		if (cond < 1) {
			goto yyc_init;
		} else {
			goto yyc_cond;
		}
	} else {
		if (cond < 3) {
			goto yyc_cond_op;
		} else {
			goto yyc_rule;
		}
	}
/* *********************************** */
yyc_init:
	{
		static const unsigned char yybm[] = {
			 80,  80,  80,  80,  80,  80,  80,  80, 
			 80,  88,   0,  80,  80,  16,  80,  80, 
			 80,  80,  80,  80,  80,  80,  80,  80, 
			 80,  80,  80,  80,  80,  80,  80,  80, 
			 88,  80,  16,  80,  80,  80,  80,  80, 
			 80,  80,  80,  80,  80,  80,  80,  80, 
			112, 112, 112, 112, 112, 112, 112, 112, 
			112, 112,  80,  80,  80,  80,  80,  80, 
			 80, 112, 112, 112, 112, 112, 112, 112, 
			112, 112, 112, 112, 112, 112, 112, 112, 
			112, 112, 112, 112, 112, 112, 112, 112, 
			112, 112, 112,  80, 144,  80,  80, 112, 
			 80, 112, 112, 112, 112, 112, 112, 112, 
			112, 112, 112, 112, 112, 112, 112, 112, 
			112, 112, 112, 112, 112, 112, 112, 112, 
			112, 112, 112,  80,  80,  80,  80,  80, 
			 80,  80,  80,  80,  80,  80,  80,  80, 
			 80,  80,  80,  80,  80,  80,  80,  80, 
			 80,  80,  80,  80,  80,  80,  80,  80, 
			 80,  80,  80,  80,  80,  80,  80,  80, 
			 80,  80,  80,  80,  80,  80,  80,  80, 
			 80,  80,  80,  80,  80,  80,  80,  80, 
			 80,  80,  80,  80,  80,  80,  80,  80, 
			 80,  80,  80,  80,  80,  80,  80,  80, 
			 80,  80,  80,  80,  80,  80,  80,  80, 
			 80,  80,  80,  80,  80,  80,  80,  80, 
			 80,  80,  80,  80,  80,  80,  80,  80, 
			 80,  80,  80,  80,  80,  80,  80,  80, 
			 80,  80,  80,  80,  80,  80,  80,  80, 
			 80,  80,  80,  80,  80,  80,  80,  80, 
			 80,  80,  80,  80,  80,  80,  80,  80, 
			 80,  80,  80,  80,  80,  80,  80,  80, 
		};
		yych = *YYCURSOR;
		if (yybm[0+yych] & 8) {
			goto yy6;
		}
		if (yych <= '#') {
			if (yych <= '\n') {
				if (yych <= 0x00) goto yy2;
				if (yych <= 0x08) goto yy4;
				goto yy9;
			} else {
				if (yych == '\r') goto yy11;
				if (yych <= '"') goto yy4;
				goto yy12;
			}
		} else {
			if (yych <= '?') {
				if (yych == ';') goto yy12;
				goto yy4;
			} else {
				if (yych <= '@') goto yy15;
				if (yych == 's') goto yy16;
				goto yy4;
			}
		}
yy2:
		++YYCURSOR;
		{ ret = SUCCESS; goto out; }
yy4:
		++YYCURSOR;
yy5:
		{ cs_error_log("Parser error on line %d", lineno); goto out; }
yy6:
		yych = *++YYCURSOR;
		if (yybm[0+yych] & 8) {
			goto yy6;
		}
		{ goto yyc_init; }
yy9:
		++YYCURSOR;
		{ lineno++; goto yyc_init; }
yy11:
		yych = *++YYCURSOR;
		if (yych == '\n') goto yy9;
		goto yy5;
yy12:
		yych = *++YYCURSOR;
		if (yybm[0+yych] & 16) {
			goto yy12;
		}
		{ goto yyc_init; }
yy15:
		yyaccept = 0;
		yych = *(YYMARKER = ++YYCURSOR);
		if (yych == 'c') goto yy17;
		if (yych == 'e') goto yy19;
		goto yy5;
yy16:
		yyaccept = 0;
		yych = *(YYMARKER = ++YYCURSOR);
		if (yych == 'e') goto yy20;
		if (yych == 'p') goto yy21;
		goto yy5;
yy17:
		yych = *++YYCURSOR;
		if (yych == 'o') goto yy23;
yy18:
		YYCURSOR = YYMARKER;
		if (yyaccept <= 1) {
			if (yyaccept == 0) {
				goto yy5;
			} else {
				yyt4 = YYCURSOR;
				goto yy45;
			}
		} else {
			goto yy45;
		}
yy19:
		yych = *++YYCURSOR;
		if (yych == 'n') goto yy24;
		goto yy18;
yy20:
		yych = *++YYCURSOR;
		if (yych == 't') goto yy25;
		goto yy18;
yy21:
		++YYCURSOR;
		{ kw_i = 0;  goto yyc_rule; }
yy23:
		yych = *++YYCURSOR;
		if (yych == 'n') goto yy26;
		goto yy18;
yy24:
		yych = *++YYCURSOR;
		if (yych == 'd') goto yy27;
		goto yy18;
yy25:
		yych = *++YYCURSOR;
		if (yych == '\t') goto yy28;
		if (yych == ' ') goto yy28;
		goto yy18;
yy26:
		yych = *++YYCURSOR;
		if (yych == 'd') goto yy30;
		goto yy18;
yy27:
		yych = *++YYCURSOR;
		if (yych == '_') goto yy31;
		goto yy18;
yy28:
		yych = *++YYCURSOR;
		if (yych <= '@') {
			if (yych <= '\t') {
				if (yych <= 0x08) goto yy18;
				goto yy28;
			} else {
				if (yych == ' ') goto yy28;
				goto yy18;
			}
		} else {
			if (yych <= '_') {
				if (yych <= 'Z') {
					yyt1 = YYCURSOR;
					goto yy32;
				}
				if (yych <= '^') goto yy18;
				yyt1 = YYCURSOR;
				goto yy32;
			} else {
				if (yych <= '`') goto yy18;
				if (yych <= 'z') {
					yyt1 = YYCURSOR;
					goto yy32;
				}
				goto yy18;
			}
		}
yy30:
		yych = *++YYCURSOR;
		if (yych == 'i') goto yy34;
		goto yy18;
yy31:
		yych = *++YYCURSOR;
		if (yych == 'c') goto yy35;
		goto yy18;
yy32:
		yych = *++YYCURSOR;
		if (yybm[0+yych] & 32) {
			goto yy32;
		}
		if (yych == '\t') {
			yyt2 = YYCURSOR;
			goto yy36;
		}
		if (yych == ' ') {
			yyt2 = YYCURSOR;
			goto yy36;
		}
		goto yy18;
yy34:
		yych = *++YYCURSOR;
		if (yych == 't') goto yy38;
		goto yy18;
yy35:
		yych = *++YYCURSOR;
		if (yych == 'o') goto yy39;
		goto yy18;
yy36:
		yych = *++YYCURSOR;
		if (yych <= 0x1F) {
			if (yych == '\t') goto yy36;
			goto yy18;
		} else {
			if (yych <= ' ') goto yy36;
			if (yych == '"') {
				yyt3 = YYCURSOR;
				goto yy40;
			}
			goto yy18;
		}
yy38:
		yych = *++YYCURSOR;
		if (yych == 'i') goto yy42;
		goto yy18;
yy39:
		yych = *++YYCURSOR;
		if (yych == 'n') goto yy43;
		goto yy18;
yy40:
		yych = *++YYCURSOR;
		if (yybm[0+yych] & 64) {
			goto yy40;
		}
		if (yych <= '\r') goto yy18;
		if (yych <= '"') goto yy44;
		goto yy46;
yy42:
		yych = *++YYCURSOR;
		if (yych == 'o') goto yy48;
		goto yy18;
yy43:
		yych = *++YYCURSOR;
		if (yych == 'd') goto yy49;
		goto yy18;
yy44:
		yych = *++YYCURSOR;
		yyt4 = YYCURSOR;
		goto yy51;
yy45:
		t1 = yyt1;
		t2 = yyt2;
		t3 = yyt3;
		t4 = yyt4;
		{
      char *key = (char*)t1;
      int keylen = t2-t1;
      zend_string *tmp = zend_hash_str_find_ptr(&vars, key, keylen);
      if (tmp) {
        zend_hash_str_del(&vars, key, keylen);
      }
      tmp = zend_string_init(t3+1, t4-t3-2, 1);
      zend_hash_str_add_ptr(&vars, key, keylen, tmp);
      goto yyc_init;
    }
yy46:
		yych = *++YYCURSOR;
		if (yybm[0+yych] & 64) {
			goto yy40;
		}
		if (yych <= '\r') goto yy18;
		if (yych <= '"') goto yy53;
		goto yy46;
yy48:
		yych = *++YYCURSOR;
		if (yych == 'n') goto yy54;
		goto yy18;
yy49:
		yych = *++YYCURSOR;
		if (yych == 'i') goto yy55;
		goto yy18;
yy50:
		yych = *++YYCURSOR;
yy51:
		if (yych <= 0x1F) {
			if (yych == '\t') goto yy50;
			goto yy45;
		} else {
			if (yych <= ' ') goto yy50;
			if (yych != ';') goto yy45;
		}
		++YYCURSOR;
		goto yy45;
yy53:
		yyaccept = 1;
		yych = *(YYMARKER = ++YYCURSOR);
		if (yybm[0+yych] & 128) {
			goto yy46;
		}
		if (yych <= 0x1F) {
			if (yych <= '\n') {
				if (yych <= 0x08) goto yy40;
				if (yych <= '\t') {
					yyt4 = YYCURSOR;
					goto yy56;
				}
				yyt4 = YYCURSOR;
				goto yy45;
			} else {
				if (yych == '\r') {
					yyt4 = YYCURSOR;
					goto yy45;
				}
				goto yy40;
			}
		} else {
			if (yych <= '"') {
				if (yych <= ' ') {
					yyt4 = YYCURSOR;
					goto yy56;
				}
				if (yych <= '!') goto yy40;
				goto yy44;
			} else {
				if (yych == ';') {
					yyt4 = YYCURSOR;
					goto yy58;
				}
				goto yy40;
			}
		}
yy54:
		yych = *++YYCURSOR;
		if (yych == '\t') goto yy59;
		if (yych == ' ') goto yy59;
		goto yy18;
yy55:
		yych = *++YYCURSOR;
		if (yych == 't') goto yy62;
		goto yy18;
yy56:
		yyaccept = 2;
		yych = *(YYMARKER = ++YYCURSOR);
		if (yybm[0+yych] & 128) {
			goto yy46;
		}
		if (yych <= 0x1F) {
			if (yych <= '\n') {
				if (yych <= 0x08) goto yy40;
				if (yych <= '\t') goto yy56;
				goto yy45;
			} else {
				if (yych == '\r') goto yy45;
				goto yy40;
			}
		} else {
			if (yych <= '"') {
				if (yych <= ' ') goto yy56;
				if (yych <= '!') goto yy40;
				goto yy44;
			} else {
				if (yych != ';') goto yy40;
			}
		}
yy58:
		yyaccept = 2;
		yych = *(YYMARKER = ++YYCURSOR);
		if (yybm[0+yych] & 64) {
			goto yy40;
		}
		if (yych <= '\r') goto yy45;
		if (yych <= '"') goto yy44;
		goto yy46;
yy59:
		yych = *++YYCURSOR;
		if (yych == '\t') goto yy59;
		if (yych == ' ') goto yy59;
		{ goto yyc_cond; }
yy62:
		yych = *++YYCURSOR;
		if (yych != 'i') goto yy18;
		yych = *++YYCURSOR;
		if (yych != 'o') goto yy18;
		yych = *++YYCURSOR;
		if (yych != 'n') goto yy18;
yy65:
		yych = *++YYCURSOR;
		if (yych <= 0x1F) {
			if (yych == '\t') goto yy65;
			goto yy18;
		} else {
			if (yych <= ' ') goto yy65;
			if (yych != ';') goto yy18;
		}
		++YYCURSOR;
		{ cond_res = 1; goto yyc_init; }
	}
/* *********************************** */
yyc_cond:
	{
		static const unsigned char yybm[] = {
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 64,  72,   0,  64,  64,   0,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 72,  64,   0,  64,  64,  64,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
			112, 112, 112, 112, 112, 112, 112, 112, 
			112, 112,  64,  64,  64,  64,  64,  64, 
			 64,  96,  96,  96,  96,  96,  96,  96, 
			 96,  96,  96,  96,  96,  96,  96,  96, 
			 96,  96,  96,  96,  96,  96,  96,  96, 
			 96,  96,  96,  64, 128,  64,  64,  96, 
			 64,  96,  96,  96,  96,  96,  96,  96, 
			 96,  96,  96,  96,  96,  96,  96,  96, 
			 96,  96,  96,  96,  96,  96,  96,  96, 
			 96,  96,  96,  64,  64,  64,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
		};
		yych = *YYCURSOR;
		if (yybm[0+yych] & 8) {
			goto yy73;
		}
		if (yych <= '/') {
			if (yych <= '\f') {
				if (yych <= 0x08) goto yy71;
				if (yych <= '\n') goto yy76;
			} else {
				if (yych <= '\r') goto yy78;
				if (yych <= 0x1F) goto yy71;
				if (yych <= '!') goto yy79;
			}
		} else {
			if (yych <= '^') {
				if (yych <= '9') {
					yyt1 = YYCURSOR;
					goto yy81;
				}
				if (yych <= '@') goto yy71;
				if (yych <= 'Z') {
					yyt1 = YYCURSOR;
					goto yy84;
				}
			} else {
				if (yych == '`') goto yy71;
				if (yych <= 'z') {
					yyt1 = YYCURSOR;
					goto yy84;
				}
			}
		}
yy71:
		++YYCURSOR;
yy72:
		{ cs_error_log("Syntax error in condition on line %d", lineno); return false; }
yy73:
		yych = *++YYCURSOR;
		if (yybm[0+yych] & 8) {
			goto yy73;
		}
		{ goto yyc_cond; }
yy76:
		++YYCURSOR;
		{ lineno++; goto yyc_cond; }
yy78:
		yych = *++YYCURSOR;
		if (yych == '\n') goto yy76;
		goto yy72;
yy79:
		++YYCURSOR;
		t1 = YYCURSOR - 1;
		{ cond_neg = (cond_neg + 1) % 2; goto yyc_cond; }
yy81:
		yych = *++YYCURSOR;
		if (yybm[0+yych] & 16) {
			goto yy81;
		}
		t1 = yyt1;
		t2 = YYCURSOR;
		{ APPLY_OP(atoi(t1));  goto yyc_cond_op; }
yy84:
		yyaccept = 0;
		yych = *(YYMARKER = ++YYCURSOR);
		if (yybm[0+yych] & 32) {
			goto yy84;
		}
		if (yych == '(') goto yy87;
yy86:
		t1 = yyt1;
		t2 = YYCURSOR;
		{
      zend_string *tmp = zend_hash_str_find_ptr(&vars, t1, t2-t1);
      if (!tmp) {
        cs_error_log("unknown variable in condition on line %d", lineno);
        goto out;
      }
      APPLY_OP(atoi(ZSTR_VAL(tmp)));
      goto yyc_cond_op;
    }
yy87:
		yych = *++YYCURSOR;
		if (yych == '"') {
			yyt2 = YYCURSOR;
			goto yy89;
		}
		if (yych == ')') {
			yyt2 = YYCURSOR;
			goto yy91;
		}
yy88:
		YYCURSOR = YYMARKER;
		if (yyaccept == 0) {
			goto yy86;
		} else {
			goto yy92;
		}
yy89:
		yych = *++YYCURSOR;
		if (yybm[0+yych] & 64) {
			goto yy89;
		}
		if (yych <= '\r') goto yy88;
		if (yych <= '"') goto yy93;
		goto yy94;
yy91:
		++YYCURSOR;
yy92:
		t1 = yyt1;
		t3 = yyt2;
		t2 = yyt2 - 1;
		t4 = YYCURSOR - 1;
		{
      if (t4-t3 >= 2 && strlen("extension_loaded") == t2-t1 && strncmp("extension_loaded", t1, t2-t1) == 0) {
        int is_loaded = (zend_hash_str_find_ptr(&module_registry, t3+1, t4-t3-2) != NULL);
        APPLY_OP(is_loaded);
      } else {
        cs_error_log("unknown function in condition on line %d", lineno);
        goto out;
      }
      goto yyc_cond_op;
    }
yy93:
		yych = *++YYCURSOR;
		if (yych == ')') goto yy91;
		goto yy88;
yy94:
		yych = *++YYCURSOR;
		if (yybm[0+yych] & 64) {
			goto yy89;
		}
		if (yych <= '\r') goto yy88;
		if (yych >= '#') goto yy94;
		yych = *++YYCURSOR;
		if (yybm[0+yych] & 128) {
			goto yy94;
		}
		if (yych <= '\r') {
			if (yych == '\n') goto yy88;
			if (yych <= '\f') goto yy89;
			goto yy88;
		} else {
			if (yych <= '"') {
				if (yych <= '!') goto yy89;
				goto yy93;
			} else {
				if (yych != ')') goto yy89;
			}
		}
		yyaccept = 1;
		yych = *(YYMARKER = ++YYCURSOR);
		if (yybm[0+yych] & 64) {
			goto yy89;
		}
		if (yych <= '\r') goto yy92;
		if (yych <= '"') goto yy93;
		goto yy94;
	}
/* *********************************** */
yyc_cond_op:
	{
		static const unsigned char yybm[] = {
			  0,   0,   0,   0,   0,   0,   0,   0, 
			  0, 128,   0,   0,   0,   0,   0,   0, 
			  0,   0,   0,   0,   0,   0,   0,   0, 
			  0,   0,   0,   0,   0,   0,   0,   0, 
			128,   0,   0,   0,   0,   0,   0,   0, 
			  0,   0,   0,   0,   0,   0,   0,   0, 
			  0,   0,   0,   0,   0,   0,   0,   0, 
			  0,   0,   0,   0,   0,   0,   0,   0, 
			  0,   0,   0,   0,   0,   0,   0,   0, 
			  0,   0,   0,   0,   0,   0,   0,   0, 
			  0,   0,   0,   0,   0,   0,   0,   0, 
			  0,   0,   0,   0,   0,   0,   0,   0, 
			  0,   0,   0,   0,   0,   0,   0,   0, 
			  0,   0,   0,   0,   0,   0,   0,   0, 
			  0,   0,   0,   0,   0,   0,   0,   0, 
			  0,   0,   0,   0,   0,   0,   0,   0, 
			  0,   0,   0,   0,   0,   0,   0,   0, 
			  0,   0,   0,   0,   0,   0,   0,   0, 
			  0,   0,   0,   0,   0,   0,   0,   0, 
			  0,   0,   0,   0,   0,   0,   0,   0, 
			  0,   0,   0,   0,   0,   0,   0,   0, 
			  0,   0,   0,   0,   0,   0,   0,   0, 
			  0,   0,   0,   0,   0,   0,   0,   0, 
			  0,   0,   0,   0,   0,   0,   0,   0, 
			  0,   0,   0,   0,   0,   0,   0,   0, 
			  0,   0,   0,   0,   0,   0,   0,   0, 
			  0,   0,   0,   0,   0,   0,   0,   0, 
			  0,   0,   0,   0,   0,   0,   0,   0, 
			  0,   0,   0,   0,   0,   0,   0,   0, 
			  0,   0,   0,   0,   0,   0,   0,   0, 
			  0,   0,   0,   0,   0,   0,   0,   0, 
			  0,   0,   0,   0,   0,   0,   0,   0, 
		};
		yych = *YYCURSOR;
		if (yybm[0+yych] & 128) {
			goto yy102;
		}
		if (yych <= ':') {
			if (yych <= '\f') {
				if (yych <= 0x08) goto yy100;
				if (yych <= '\n') goto yy105;
			} else {
				if (yych <= '\r') goto yy107;
				if (yych == '&') {
					yyt1 = YYCURSOR;
					goto yy108;
				}
			}
		} else {
			if (yych <= '=') {
				if (yych <= ';') goto yy109;
				if (yych <= '<') {
					yyt1 = YYCURSOR;
					goto yy111;
				}
				yyt1 = YYCURSOR;
				goto yy113;
			} else {
				if (yych <= '>') {
					yyt1 = YYCURSOR;
					goto yy111;
				}
				if (yych == '|') {
					yyt1 = YYCURSOR;
					goto yy114;
				}
			}
		}
yy100:
		++YYCURSOR;
yy101:
		{ cs_error_log("Syntax error in condition on line %d", lineno); return false; }
yy102:
		yych = *++YYCURSOR;
		if (yybm[0+yych] & 128) {
			goto yy102;
		}
		{ goto yyc_cond_op; }
yy105:
		++YYCURSOR;
		{ lineno++; goto yyc_cond_op; }
yy107:
		yych = *++YYCURSOR;
		if (yych == '\n') goto yy105;
		goto yy101;
yy108:
		yych = *++YYCURSOR;
		if (yych == '&') goto yy111;
		goto yy101;
yy109:
		++YYCURSOR;
		{ goto yyc_init; }
yy111:
		++YYCURSOR;
		t1 = yyt1;
		{ cond_op = *t1; goto yyc_cond; }
yy113:
		yych = *++YYCURSOR;
		if (yych == '=') goto yy111;
		goto yy101;
yy114:
		yych = *++YYCURSOR;
		if (yych == '|') goto yy111;
		goto yy101;
	}
/* *********************************** */
yyc_rule:
	{
		static const unsigned char yybm[] = {
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 64,  88,  16,  64,  64,   0,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 88,  64,   0,  64,  64,  64,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 96,  96,  96,  96,  96,  96,  96,  96, 
			 96,  96,  64,  64,  64,  64,  64,  64, 
			 64,  96,  96,  96,  96,  96,  96,  96, 
			 96,  96,  96,  96,  96,  96,  96,  96, 
			 96,  96,  96,  96,  96,  96,  96,  96, 
			 96,  96,  96,  64, 128,  64,  64,  96, 
			 64,  96,  96,  96,  96,  96,  96,  96, 
			 96,  96,  96,  96,  96,  96,  96,  96, 
			 96,  96,  96,  96,  96,  96,  96,  96, 
			 96,  96,  96,  64,  64,  64,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
		};
		yych = *YYCURSOR;
		if (yybm[0+yych] & 8) {
			goto yy119;
		}
		if (yych <= '\r') {
			if (yych <= 0x08) goto yy117;
			if (yych <= '\n') goto yy122;
			if (yych >= '\r') goto yy123;
		} else {
			if (yych <= '.') {
				if (yych >= '.') goto yy124;
			} else {
				if (yych == ';') goto yy125;
			}
		}
yy117:
		++YYCURSOR;
yy118:
		{ goto end_of_rule; }
yy119:
		yych = *++YYCURSOR;
		if (yybm[0+yych] & 8) {
			goto yy119;
		}
		{  goto yyc_rule; }
yy122:
		yyaccept = 0;
		yych = *(YYMARKER = ++YYCURSOR);
		if (yych <= '\r') {
			if (yych <= 0x08) goto yy118;
			if (yych <= '\n') {
				yyt1 = YYCURSOR;
				goto yy127;
			}
			if (yych <= '\f') goto yy118;
			yyt1 = YYCURSOR;
			goto yy130;
		} else {
			if (yych <= ' ') {
				if (yych <= 0x1F) goto yy118;
				yyt1 = YYCURSOR;
				goto yy127;
			} else {
				if (yych == '.') {
					yyt1 = YYCURSOR;
					goto yy131;
				}
				goto yy118;
			}
		}
yy123:
		yyaccept = 0;
		yych = *(YYMARKER = ++YYCURSOR);
		if (yych == '\n') goto yy133;
		goto yy118;
yy124:
		yych = *++YYCURSOR;
		if (yych <= '^') {
			if (yych <= '@') goto yy118;
			if (yych <= 'Z') {
				yyt1 = YYCURSOR;
				goto yy134;
			}
			goto yy118;
		} else {
			if (yych == '`') goto yy118;
			if (yych <= 'z') {
				yyt1 = YYCURSOR;
				goto yy134;
			}
			goto yy118;
		}
yy125:
		++YYCURSOR;
		{
      end_of_rule:
      if (!cond_res) { goto yyc_init; }
      parsed_rule[kw_i++] = (sp_parsed_keyword){0, 0, 0, 0, 0, 0};
      if (process_rule && process_rule(parsed_rule) != SUCCESS) {
        goto out;
      }
      goto yyc_init;
    }
yy127:
		yych = *++YYCURSOR;
		if (yybm[0+yych] & 16) {
			goto yy127;
		}
		if (yych == '\r') goto yy130;
		if (yych == '.') goto yy131;
yy129:
		YYCURSOR = YYMARKER;
		if (yyaccept <= 1) {
			if (yyaccept == 0) {
				goto yy118;
			} else {
				yyt3 = yyt4 = NULL;
				yyt2 = YYCURSOR;
				goto yy136;
			}
		} else {
			goto yy136;
		}
yy130:
		yych = *++YYCURSOR;
		if (yych == '\n') goto yy127;
		goto yy129;
yy131:
		++YYCURSOR;
		YYCURSOR = yyt1;
		{  lineno++; goto yyc_rule; }
yy133:
		yych = *++YYCURSOR;
		if (yych <= '\r') {
			if (yych <= 0x08) goto yy129;
			if (yych <= '\n') {
				yyt1 = YYCURSOR;
				goto yy127;
			}
			if (yych <= '\f') goto yy129;
			yyt1 = YYCURSOR;
			goto yy130;
		} else {
			if (yych <= ' ') {
				if (yych <= 0x1F) goto yy129;
				yyt1 = YYCURSOR;
				goto yy127;
			} else {
				if (yych == '.') {
					yyt1 = YYCURSOR;
					goto yy131;
				}
				goto yy129;
			}
		}
yy134:
		yyaccept = 1;
		yych = *(YYMARKER = ++YYCURSOR);
		if (yybm[0+yych] & 32) {
			goto yy134;
		}
		if (yych == '(') {
			yyt2 = YYCURSOR;
			goto yy137;
		}
		yyt3 = yyt4 = NULL;
		yyt2 = YYCURSOR;
yy136:
		t1 = yyt1;
		t2 = yyt2;
		t3 = yyt3;
		t4 = yyt4;
		{
      if (!cond_res) { goto yyc_rule; }
      if (kw_i == max_keywords) {
        cs_error_log("Too many keywords in rule (more than %d) on line %d", max_keywords, lineno);
        goto out;
      }
      sp_parsed_keyword kw = {.kw = (char*)t1, .kwlen = t2-t1, .arg = (char*)t3, .arglen = t4-t3, .argtype = SP_ARGTYPE_UNKNOWN, .lineno = lineno};
      if (t3 && t4) {
        if (t3 == t4) {
          kw.argtype = SP_ARGTYPE_EMPTY;
        } else if (t4-t3 >= 2 && *t3 == '"') {
          kw.arg = (char*)t3 + 1;
          kw.arglen = t4 - t3 - 2;
          kw.argtype = SP_ARGTYPE_STR;
        } else {
          zend_string *tmp = zend_hash_str_find_ptr(&vars, t3, t4-t3);
          if (!tmp) {
            cs_error_log("unknown variable on line %d", lineno);
            goto out;
          }
          kw.arg = ZSTR_VAL(tmp);
          kw.arglen = ZSTR_LEN(tmp);
          kw.argtype = SP_ARGTYPE_STR;
        }
      } else {
        kw.argtype = SP_ARGTYPE_NONE;
      }
      parsed_rule[kw_i++] = kw;
      goto yyc_rule;
    }
yy137:
		yych = *++YYCURSOR;
		if (yych <= '@') {
			if (yych <= '"') {
				if (yych <= '!') goto yy129;
				yyt3 = YYCURSOR;
			} else {
				if (yych == ')') {
					yyt3 = yyt4 = YYCURSOR;
					goto yy140;
				}
				goto yy129;
			}
		} else {
			if (yych <= '_') {
				if (yych <= 'Z') {
					yyt3 = YYCURSOR;
					goto yy141;
				}
				if (yych <= '^') goto yy129;
				yyt3 = YYCURSOR;
				goto yy141;
			} else {
				if (yych <= '`') goto yy129;
				if (yych <= 'z') {
					yyt3 = YYCURSOR;
					goto yy141;
				}
				goto yy129;
			}
		}
yy138:
		yych = *++YYCURSOR;
		if (yybm[0+yych] & 64) {
			goto yy138;
		}
		if (yych <= '\r') goto yy129;
		if (yych <= '"') goto yy143;
		goto yy144;
yy140:
		++YYCURSOR;
		goto yy136;
yy141:
		yych = *++YYCURSOR;
		if (yych <= '@') {
			if (yych <= ')') {
				if (yych <= '(') goto yy129;
				yyt4 = YYCURSOR;
				goto yy140;
			} else {
				if (yych <= '/') goto yy129;
				if (yych <= '9') goto yy141;
				goto yy129;
			}
		} else {
			if (yych <= '_') {
				if (yych <= 'Z') goto yy141;
				if (yych <= '^') goto yy129;
				goto yy141;
			} else {
				if (yych <= '`') goto yy129;
				if (yych <= 'z') goto yy141;
				goto yy129;
			}
		}
yy143:
		yych = *++YYCURSOR;
		if (yych == ')') {
			yyt4 = YYCURSOR;
			goto yy140;
		}
		goto yy129;
yy144:
		yych = *++YYCURSOR;
		if (yybm[0+yych] & 64) {
			goto yy138;
		}
		if (yych <= '\r') goto yy129;
		if (yych >= '#') goto yy144;
		yych = *++YYCURSOR;
		if (yybm[0+yych] & 128) {
			goto yy144;
		}
		if (yych <= '\r') {
			if (yych == '\n') goto yy129;
			if (yych <= '\f') goto yy138;
			goto yy129;
		} else {
			if (yych <= '"') {
				if (yych <= '!') goto yy138;
				goto yy143;
			} else {
				if (yych != ')') goto yy138;
				yyt4 = YYCURSOR;
			}
		}
		yyaccept = 2;
		yych = *(YYMARKER = ++YYCURSOR);
		if (yybm[0+yych] & 64) {
			goto yy138;
		}
		if (yych <= '\r') goto yy136;
		if (yych <= '"') goto yy143;
		goto yy144;
	}
}

out:
  zend_hash_destroy(&vars);
  return ret;
}