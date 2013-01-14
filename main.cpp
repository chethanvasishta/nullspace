#include <iostream>
#include <alsa/asoundlib.h>
using namespace std;

void countCards(){
	int err, cardnum, totalCards = 0;
	cardnum = -1;
	while(1){
		if((err = snd_card_next(&cardnum)) < 0){
			cout<<"Error while fetching next sound card"<<endl;
			break;
		}
		if(cardnum < 0) break;		
		++totalCards;		
	}
	cout<<"We found "<<totalCards<<" on this system!"<<endl;
}

int main(){
    cout<<"Noise cancellation program";
    countCards();
    return 0;
}
