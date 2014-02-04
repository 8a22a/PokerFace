#include "pebble.h"

static Window* window;
static GBitmap *background_image_container;

static TextLayer *hour1_layer;
static char hour1_text[] = "00";

static TextLayer *hour2_layer;
static char hour2_text[] = "00";

static TextLayer *minute1_layer;
static char minute1_text[] = "00";

static TextLayer *minute2_layer;
static char minute2_text[] = "00";

static TextLayer *minute3_layer;
static char minute3_text[] = "00";

static TextLayer *date_layer;
static char date_text[] = "00";

static TextLayer *month_layer;
static char month_text[] = "00";

static TextLayer *year_layer;
static char year_text[] = "00";

#define GRECT_FULL_WINDOW GRect(0,0,144,168)

static Layer *background_layer;
static Layer *window_layer;


void draw_hour1(){
  time_t now = time(NULL);
  struct tm *t = localtime(&now);
  strftime(hour1_text, sizeof(hour1_text), "%H", t);
  hour1_text[1]=0; //display only first digit of hour
	if (hour1_text[0] == '1'){
     text_layer_set_text(hour1_layer, "A"); //display 1 as A         
     } else
    if (hour1_text[0] == '0'){
     text_layer_set_text(hour1_layer, "Q"); //display 0 as Q        
     } else {
   text_layer_set_text(hour1_layer, hour1_text);       
   }	 
}

void draw_hour2(){
  time_t now = time(NULL);
  struct tm *t = localtime(&now);
  strftime(hour2_text, sizeof(hour2_text), "%H", t);
     if (hour2_text[1] == '1'){
     text_layer_set_text(hour2_layer, "A");          
     } else
     if (hour2_text[1] == '0'){
     text_layer_set_text(hour2_layer, "Q");         
     } else {
     text_layer_set_text(hour2_layer, hour2_text+1); //display only second digit of hour      
   }	
}

void draw_minute1(){
  time_t now = time(NULL);
  struct tm *t = localtime(&now);
  strftime(minute1_text, sizeof(minute1_text), "%M", t);
  minute1_text[1]=0;
	if (minute1_text[0] == '1'){
     text_layer_set_text(minute1_layer, "A");          
     } else
    if (minute1_text[0] == '0'){
     text_layer_set_text(minute1_layer, "Q");         
     } else {
   text_layer_set_text(minute1_layer, minute1_text);       
   }
}

void draw_minute2(){
  time_t now = time(NULL);
  struct tm *t = localtime(&now);
  strftime(minute2_text, sizeof(minute2_text), "%M", t);
    if (minute2_text[1] == '1'){
     text_layer_set_text(minute2_layer, "A");          
     } else
     if (minute2_text[1] == '0'){
     text_layer_set_text(minute2_layer, "Q");         
     } else {
     text_layer_set_text(minute2_layer, minute2_text+1);      
   }	
}

void draw_minute3(){
  time_t now = time(NULL);
  struct tm *t = localtime(&now);
  strftime(minute3_text, sizeof(minute3_text), "%M", t);
    if (minute3_text[1] == '1'){
     text_layer_set_text(minute3_layer, "A");          
     } else
     if (minute3_text[1] == '0'){
     text_layer_set_text(minute3_layer, "Q");         
     } else {
     text_layer_set_text(minute3_layer, minute3_text+1);       
   }	
}

void draw_date(){
  time_t now = time(NULL);
  struct tm *t = localtime(&now);
  strftime(date_text, sizeof(date_text), "%d", t);
  text_layer_set_text(date_layer, date_text);
}

void draw_month(){
  time_t now = time(NULL);
  struct tm *t = localtime(&now);
  strftime(month_text, sizeof(month_text), "%m", t);
  text_layer_set_text(month_layer, month_text);
}

void draw_year(){
  time_t now = time(NULL);
  struct tm *t = localtime(&now);
  strftime(year_text, sizeof(year_text), "%y", t);
  text_layer_set_text(year_layer, year_text);
}

void draw_background_callback(Layer *layer, GContext *ctx) {
        graphics_context_set_compositing_mode(ctx, GCompOpAssign);
        graphics_draw_bitmap_in_rect(ctx, background_image_container,
                        GRECT_FULL_WINDOW);
}

void handle_minute_tick(struct tm *tick_time, TimeUnits units_changed) {
   draw_hour1();
   draw_hour2();
   draw_minute1();
   draw_minute2();
   draw_minute3();
   draw_date();
   draw_month();
   draw_year();
}

// Handle the start-up of the app
void init(void) {

  // Window
  window = window_create();
  window_stack_push(window, true /* Animated */);
  window_layer = window_get_root_layer(window);

  // Background image
  background_image_container = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BACKGROUND);
  background_layer = layer_create(GRECT_FULL_WINDOW);
  layer_set_update_proc(background_layer, &draw_background_callback);
  layer_add_child(window_layer, background_layer);

  hour1_layer = text_layer_create(GRect(12, 26, 20, 20));
  text_layer_set_text_alignment(hour1_layer, GTextAlignmentCenter);
  text_layer_set_text_color(hour1_layer, GColorBlack);
  text_layer_set_background_color(hour1_layer, GColorClear);
  text_layer_set_font(hour1_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_ARIAL_BOLD_12)));
  layer_add_child(window_layer, text_layer_get_layer(hour1_layer));
  draw_hour1();	
	
  hour2_layer = text_layer_create(GRect(32, 17, 20, 20));
  text_layer_set_text_alignment(hour2_layer, GTextAlignmentCenter);
  text_layer_set_text_color(hour2_layer, GColorBlack);
  text_layer_set_background_color(hour2_layer, GColorClear);
  text_layer_set_font(hour2_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_ARIAL_BOLD_12)));
  layer_add_child(window_layer, text_layer_get_layer(hour2_layer));
  draw_hour2();	
 
  minute1_layer = text_layer_create(GRect(53, 12, 20, 20));
  text_layer_set_text_alignment(minute1_layer, GTextAlignmentCenter);
  text_layer_set_text_color(minute1_layer, GColorBlack);
  text_layer_set_background_color(minute1_layer, GColorClear);
  text_layer_set_font(minute1_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_ARIAL_BOLD_12)));
  layer_add_child(window_layer, text_layer_get_layer(minute1_layer));
  draw_minute1();	
	
  minute2_layer = text_layer_create(GRect(77, 12, 20, 20));
  text_layer_set_text_alignment(minute2_layer, GTextAlignmentCenter);
  text_layer_set_text_color(minute2_layer, GColorBlack);
  text_layer_set_background_color(minute2_layer, GColorClear);
  text_layer_set_font(minute2_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_ARIAL_BOLD_12)));
  layer_add_child(window_layer, text_layer_get_layer(minute2_layer));
  draw_minute2();	
	
  minute3_layer = text_layer_create(GRect(107, 90, 20, 20));
  text_layer_set_text_alignment(minute3_layer, GTextAlignmentCenter);
  text_layer_set_text_color(minute3_layer, GColorBlack);
  text_layer_set_background_color(minute3_layer, GColorClear);
  text_layer_set_font(minute3_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_ARIAL_BOLD_12)));
  layer_add_child(window_layer, text_layer_get_layer(minute3_layer));
  draw_minute3();	
	
  date_layer = text_layer_create(GRect(22, 132, 20, 20));
  text_layer_set_text_alignment(date_layer, GTextAlignmentCenter);
  text_layer_set_text_color(date_layer, GColorBlack);
  text_layer_set_background_color(date_layer, GColorClear);
  text_layer_set_font(date_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_ARIAL_BOLD_12)));
  layer_add_child(window_layer, text_layer_get_layer(date_layer));
  draw_date();	
	
  month_layer = text_layer_create(GRect(63, 127, 20, 20));
  text_layer_set_text_alignment(month_layer, GTextAlignmentCenter);
  text_layer_set_text_color(month_layer, GColorBlack);
  text_layer_set_background_color(month_layer, GColorClear);
  text_layer_set_font(month_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_ARIAL_BOLD_12)));
  layer_add_child(window_layer, text_layer_get_layer(month_layer));
  draw_month();
	
  year_layer = text_layer_create(GRect(103, 132, 20, 20));
  text_layer_set_text_alignment(year_layer, GTextAlignmentCenter);
  text_layer_set_text_color(year_layer, GColorBlack);
  text_layer_set_background_color(year_layer, GColorClear);
  text_layer_set_font(year_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_ARIAL_BOLD_12)));
  layer_add_child(window_layer, text_layer_get_layer(year_layer));
  draw_year();	
					
  tick_timer_service_subscribe(MINUTE_UNIT, handle_minute_tick);
}	

void deinit() {
  window_destroy(window);
  gbitmap_destroy(background_image_container);
  text_layer_destroy(hour1_layer);
  text_layer_destroy(hour2_layer);
  text_layer_destroy(minute1_layer);
  text_layer_destroy(minute2_layer);
  text_layer_destroy(minute3_layer);
  text_layer_destroy(date_layer);
  text_layer_destroy(month_layer);
  text_layer_destroy(year_layer); 
}


int main(void) {
  init();
  app_event_loop();
  deinit();
}