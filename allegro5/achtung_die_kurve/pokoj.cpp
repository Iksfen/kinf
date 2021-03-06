//
// Szablon gry w Allegro 5. (C) Kółko Informatyczne Szkoły Żagle
//

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "client.h"

#include <iostream>
using namespace std;

//
// Konfiguracja gry
//

const int screen_w = 1000;   // szerokość ekranu (screen width)
const int screen_h = 562;   // wysokość ekranu (screen height)


/****************************************
 * Kod poniżej jest w miarę generyczny  *
 ****************************************/
 
const float FPS = 60;       // Frames Per Second
bool key[ALLEGRO_KEY_MAX];  // wciśnięte klawisze

ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *timer = NULL;

int init()
{
    if(!al_init()) {
        cerr << "Błąd podczas inicjalizacji allegro." << endl;
        return -1;
    }
  
    if (!al_init_primitives_addon()) {
        cerr << "Błąd podczas inicjalizacji dodatku 'primitives'." << endl;
        return -1;
    }
    
    if (!al_install_keyboard()) {
        cerr << "Błąd podczas inicjalizacji klawiatury." << endl;
        return -1;
    }

    if (!al_install_mouse()) {
        cerr << "Błąd podczas inicjalizacji myszy." << endl;
        return -1;
    }
  
    timer = al_create_timer(1.0 / FPS);
    if(!timer) {
        cerr << "Błąd podczas inicjalizacji zegara." << endl;
        return -1;
    }
 
    display = al_create_display(screen_w, screen_h);
    if(!display) {
        cerr << "Błąd podczas inicjalizacji ekranu." << endl;
        al_destroy_timer(timer);
        return -1;
    }

    event_queue = al_create_event_queue();
    if(!event_queue) {
        cerr << "Błąd podczas inicjalizacji kolejki zdarzeń." << endl;
        al_destroy_display(display);
        al_destroy_timer(timer);
        return -1;
    }
  
    al_register_event_source(event_queue, al_get_display_event_source(display));  
    al_register_event_source(event_queue, al_get_timer_event_source(timer));  
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_clear_to_color(al_map_rgb(0,0,0));
  
    al_flip_display();  
    al_start_timer(timer);

    return 0;
}

/****************************************
 * Tu rozpoczyna się istotna część kodu *
 ****************************************/
 
//
// Struktury danych
//
int max_graczy=10;
struct type_of_player{
	float x;
	float y;
};
type_of_player player[max_graczy];

//
// Zmienne
//
void ustawienia_poczatkowe(){
	for(int i=0;i<max_graczy;i++){
		player[i].x=-100;
		player[i].y=-100;	}
}
void odbieranie_paczek(){
	string packet;
	service_websockets();
	while(receive_packet(packet)){
		if(packet.substr(1,9)=="position"){
			int gr=(int)packet[0]-'0';
			int mndz=1;//mnozenie dziesiatek
			int ilosc_cyfr=0;
			player[gr].x=0;		
			player[gr].y=0;
			for(int i=9;i<packet.length();i++){
				if(packet[i]==','){break;}
				ilosc_cyfr++;
			}
			for(int i=9+ilosc_cyfr;i>=9;i--){
				player[gr].x=player[gr].x+((int)packet[i]-'0')*mndz;
				mndz=mndz*10;
			}
			ilosc_cyfr=0;
			mndz=1;
			for(int i=9+ilosc_cyfr;i<packet.length();i++){
				ilosc_cyfr++;
			}
			for(int i=packet.length()-1;i>=9+ilosc_cyfr;i--){
				player[gr].y=player[gr].y+((int)packet[i]-'0')*mndz;
				mndz=mndz*10;
			}
			service_websockets();
					
		}
	}
}
//
// Rysowanie planszy
//

void rysuj_plansze()
{
	float radius=10;
	    al_clear_to_color(al_map_rgb(0,0,0));
	for(int i=0;i<max_player;i++){
		al_draw_filled_circle(player[i].x, player[i].y, radius, al_map_rgb(23, 232, 100));
	}

}

//
// Mechanika gry
//

void aktualizuj_plansze()
{
	odbieranie_paczek();
}

//
// Reakcja na akcje graczy
//

void co_robia_gracze()
{
}


//
//INT MAIN
//
int main(int argc, char ** argv)
{
    if (init() != 0) {
        cerr << "Inicjalizacja nie powiodła się." << endl;
        return -1;
    }
	ustawienia_poczatkowe();
 
    bool przerysuj = true;
    bool wyjdz = false;  

    //
    // Event loop - główna pętla programu
    //
        
    while(!wyjdz)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if(ev.type == ALLEGRO_EVENT_TIMER) {
            //
            // minęła 1/60 (1/FPS) część sekundy
            //
            przerysuj = true;

            co_robia_gracze();

            aktualizuj_plansze();

        } else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            key[ev.keyboard.keycode] = true;
        } else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
            key[ev.keyboard.keycode] = false;
            
            if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                wyjdz = true;
            }
        }

        if(przerysuj && al_is_event_queue_empty(event_queue)) {
            przerysuj = false;

            rysuj_plansze();

            al_flip_display();
         }    
    }

    return 0;
}
