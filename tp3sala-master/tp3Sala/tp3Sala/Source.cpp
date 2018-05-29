#include <stdio.h>
#include <allegro5/allegro.h>
#include<allegro5/allegro_image.h>
#include<allegro5/allegro_native_dialog.h>
#include<iostream>

using namespace std;


int main(int argc, char **argv){


	ALLEGRO_DISPLAY * display;
	ALLEGRO_EVENT_QUEUE *queue;
	ALLEGRO_BITMAP * bitmap = NULL;
	ALLEGRO_BITMAP *bitmap2 = NULL;

	al_init();
	display = al_create_display(800, 600);
	queue = al_create_event_queue();

	al_install_keyboard();
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(display));
	al_init_image_addon();

	bitmap = al_load_bitmap("Blue_01.png");
	bitmap2 = al_load_bitmap("Blue_01.png");

	bool running = true;

	float x = 0;
	float y = 0;

	float x2 = 300;
	float y2 = 300;
	float velocity = 4.5f;

	float widthBitmap1 = al_get_bitmap_width(bitmap);
	float heightBitmap1 = al_get_bitmap_height(bitmap);

	float widthBitmap2 = al_get_bitmap_width(bitmap2);
	float heightBitmap2 = al_get_bitmap_height(bitmap2);

	cout << "width bitmap 1" << widthBitmap1<<endl;
	cout << "height bitmap 1" << heightBitmap1 << endl;

	while (running) {
		al_clear_to_color(al_map_rgba_f(1, 1, 1, 1));
		al_draw_bitmap(bitmap, x,y, 0);
		al_draw_bitmap(bitmap2, x2, y2, 0);
		al_flip_display();

		ALLEGRO_EVENT event;
		al_wait_for_event(queue, &event);
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			running = false;
	
		ALLEGRO_KEYBOARD_STATE keyState;
		al_get_keyboard_state(&keyState);
		if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT))
		{
			x += velocity;
		}	
		if (al_key_down(&keyState, ALLEGRO_KEY_LEFT))
		{
			x -= velocity;
		}
		if (al_key_down(&keyState, ALLEGRO_KEY_UP)) {
			y -= velocity;
		}
		if (al_key_down(&keyState, ALLEGRO_KEY_DOWN)) {
			y += velocity;
		}

		cout << "posx1 " << x << endl;
		cout << "posx2 " << x2 << endl;

		if (x + widthBitmap1 > x2 && x < x2 + widthBitmap2 && y<y2 + heightBitmap2 && y + heightBitmap1 > y2) {
			cout << "contacto" << endl;
			running = false;
		}
	}

	al_destroy_display(display);
	al_uninstall_keyboard();
	al_destroy_bitmap(bitmap);
	al_destroy_bitmap(bitmap2);

	return 0;
}