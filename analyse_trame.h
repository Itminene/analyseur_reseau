#ifndef ANALYSE_TRAME_H
#define ANALYSE_TRAME_H

#include "lecture_trame.h"
#include "analyse_trame_bis.h"
int read_ethernet(Trame *trame);
int read_ip(Trame* trame);
int get_ip(Trame* trame,Trame **segment,int src[4],int dst[4]);
int get_tcp(Trame* trame,Trame **data,Tcp_brut* tcp_brut,int src[4],int dst[4]);
Cell_Printable* tcp_to_str(Tcp_brut* tcp_brut);
Cell_Printable* tcp_to_http(Trame*data,Tcp_brut* tcp_brut);
Cell_Printable* trame_brut_to_str(Trame* trame);
List_Printable* trace_brut_to_str(Trace* trace);
Trame* get_options(Trame *options,Tcp_brut* tcp_brut, int *cpt, int *thl);
int generate_file(FILE* fichier,List_Printable*lp);
int generate_line_file(Printable* p, char* line);
#endif