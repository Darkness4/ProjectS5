#ifndef _manip_fichier_h
#define _manip_fichier_h

const char* FICHIER_DATA;

int convert_Minutes_to_Hour(int *minutes_to_hour);
void ecrireList(struct ListeClients *tete);
double fileMoy(void);
int fileMax(void);
double debMoy(void);
double tauxTraite(void);
double tempsRep(void);

#endif  // _manip_fichier_h
