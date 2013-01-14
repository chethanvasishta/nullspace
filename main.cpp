#include <iostream>
#include <cstring>
#include <alsa/asoundlib.h>
using namespace std;

void printCardInfo(int cardNum){
	char str[255];
	sprintf(str, "hw:%d", cardNum);
	
	int err;
	snd_ctl_t *cardHandle;
	snd_ctl_card_info_t *cardInfo;
	if((err = snd_ctl_open(&cardHandle, str, 0)) < 0){
		cout<<"Cannot open card# "<<cardNum<<endl;		
	}else{
		// We need to get a snd_ctl_card_info_t. Just alloc it on the stack
		snd_ctl_card_info_alloca(&cardInfo);
		
		// Tell ALSA to fill in our snd_ctl_card_info_t with info about this card
		if ((err = snd_ctl_card_info(cardHandle, cardInfo)) < 0)
			cout<<"Can't get info for card "<<cardNum<<" : " << snd_strerror(err) <<endl;
		else
			cout<<"Card "<<cardNum<<" : "<< snd_ctl_card_info_get_name(cardInfo) <<endl;

		// Close the card's control interface after we're done with it
		snd_ctl_close(cardHandle);
      }
}

void countCards(){
	int err, cardnum, totalCards = 0;
	cardnum = -1;
	while(1){
		if((err = snd_card_next(&cardnum)) < 0){
			cout<<"Error while fetching next sound card"<<endl;
			break;
		}
		
		// No more cards? ALSA sets "cardNum" to -1 if so
	 	if(cardnum < 0) break;
		++totalCards;

		printCardInfo(cardnum);
	}
	cout<<"We found "<<totalCards<<" cards on this system!"<<endl;
	
	// ALSA allocates some mem to load its config file when we call
	// snd_card_next. Now that we're done getting the info, let's tell ALSA
	// to unload the info and free up that mem
	snd_config_update_free_global(); 
}

int main(){
    cout<<"Noise cancellation program!"<<endl;
    countCards();
    return 0;
}
