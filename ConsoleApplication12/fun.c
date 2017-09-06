//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//
//struct card
//{
//	const char *face;
//	const char *suit;
//};
//
//typedef struct card Card;
//void fillDeck(Card * const, const char *[],const char *[]);
//void shuffle(Card * const);
//void deal(const Card * const);
//
//int main()
//{
//	FILE *file= fopen("D:\\vstest\\switch.txt", "w+");
//	Card deck[52];
//	//Card *p = 0;
//	const char *face[] = { "Ace", "Deuce", "Three",
//		"Four", "Five",
//		"Six", "Seven", "Eight",
//		"Nine", "Ten",
//		"Jack", "Queen", "King" };
//	const char *suit[] = { "Hearts", "Diamonds",
//		"Clubs", "Spades" };
//
//	fillDeck(deck, face, suit);
//	shuffle(deck);
//	deal(file,deck);
//	fclose(file);
//	return 0;
//}
//
//void fillDeck(Card * const wDeck, const char * wFace[],const char * wSuit[])
//{
//
//	for (int i = 0; i <= 51; i++)
//	{
//		wDeck[i].face = wFace[i % 13];
//		wDeck[i].suit = wSuit[i / 13];
//	}
//}
//
//void shuffle(Card * const wDeck)
//{
//	srand(time(NULL));
//	//Card temp;//temp 只生成一次
//	for (int i = 0; i <= 51; i++)
//	{
//		int j = rand() % 52;
//		Card temp = wDeck[i];
//		wDeck[i] = wDeck[j];
//		wDeck[j] = temp;
//	}
//}
//
//void deal(FILE *f,const Card * const wDeck)
//{
//	for (int i = 0; i <= 51; i++)
//	{
//		fprintf(f,"%5s of %-8s%c", wDeck[i].face,
//			wDeck[i].suit,
//			(i + 1) % 2 ? '\t' : '\n');
//	}
//}

#include"Header.h"