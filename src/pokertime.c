#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"


#define MY_UUID { 0x73, 0x39, 0xC9, 0x82, 0x6C, 0xA8, 0x4B, 0x6D, 0x94, 0x89, 0x30, 0x17, 0xA3, 0xC1, 0xB0, 0x6D }
PBL_APP_INFO(MY_UUID,
             "Poker Time", "8a22a",
             1, 0, /* App version */
             RESOURCE_ID_IMAGE_MENU_ICON,
             APP_INFO_WATCH_FACE);

Window window;

TextLayer hour1_layer;
GFont hour1_font;
static char hour1_text[] = "00";

TextLayer hour2_layer;
GFont hour2_font;
static char hour2_text[] = "00";

TextLayer minute1_layer;
GFont minute1_font;
static char minute1_text[] = "00";

TextLayer minute2_layer;
GFont minute2_font;
static char minute2_text[] = "00";

TextLayer minute3_layer;
GFont minute3_font;
static char minute3_text[] = "00";

TextLayer date_layer;
GFont date_font;
static char date_text[] = "00";

TextLayer month_layer;
GFont month_font;
static char month_text[] = "00";

TextLayer year_layer;
GFont year_font;
static char year_text[] = "00";

BmpContainer background_image_container;

void draw_hour1(){
  PblTm t;
  get_time(&t);
  string_format_time(hour1_text, sizeof(hour1_text), "%H", &t);
  hour1_text[1]=0; //display only first digit of hour
	if (hour1_text[0] == '1'){
     text_layer_set_text(&hour1_layer, "A"); //display 1 as A         
     } else
    if (hour1_text[0] == '0'){
     text_layer_set_text(&hour1_layer, "Q"); //display 0 as Q        
     } else {
   text_layer_set_text(&hour1_layer, hour1_text);       
   }	 
}

void draw_hour2(){
  PblTm t;
  get_time(&t);
  string_format_time(hour2_text, sizeof(hour2_text), "%H", &t);
     if (hour2_text[1] == '1'){
     text_layer_set_text(&hour2_layer, "A");          
     } else
     if (hour2_text[1] == '0'){
     text_layer_set_text(&hour2_layer, "Q");         
     } else {
     text_layer_set_text(&hour2_layer, hour2_text+1); //display only second digit of hour      
   }	
}

void draw_minute1(){
  PblTm t;
  get_time(&t);
  string_format_time(minute1_text, sizeof(minute1_text), "%M", &t);
  minute1_text[1]=0;
	if (minute1_text[0] == '1'){
     text_layer_set_text(&minute1_layer, "A");          
     } else
    if (minute1_text[0] == '0'){
     text_layer_set_text(&minute1_layer, "Q");         
     } else {
   text_layer_set_text(&minute1_layer, minute1_text);       
   }
}

void draw_minute2(){
  PblTm t;
  get_time(&t);
  string_format_time(minute2_text, sizeof(minute2_text), "%M", &t);
    if (minute2_text[1] == '1'){
     text_layer_set_text(&minute2_layer, "A");          
     } else
     if (minute2_text[1] == '0'){
     text_layer_set_text(&minute2_layer, "Q");         
     } else {
     text_layer_set_text(&minute2_layer, minute2_text+1);       
   }	
}

void draw_minute3(){
  PblTm t;
  get_time(&t);
  string_format_time(minute3_text, sizeof(minute3_text), "%M", &t);
    if (minute3_text[1] == '1'){
     text_layer_set_text(&minute3_layer, "A");          
     } else
     if (minute3_text[1] == '0'){
     text_layer_set_text(&minute3_layer, "Q");         
     } else {
     text_layer_set_text(&minute3_layer, minute3_text+1);       
   }	
}

void draw_date(){
  PblTm t;
  get_time(&t);
  string_format_time(date_text, sizeof(date_text), "%d", &t);
  text_layer_set_text(&date_layer, date_text);
}

void draw_month(){
  PblTm t;
  get_time(&t);
  string_format_time(month_text, sizeof(month_text), "%m", &t);
  text_layer_set_text(&month_layer, month_text);
}

void draw_year(){
  PblTm t;
  get_time(&t);
  string_format_time(year_text, sizeof(year_text), "%y", &t);
  text_layer_set_text(&year_layer, year_text);
}

void update_watch(PblTm* t){
  draw_hour1();
  draw_hour2();
  draw_minute1();
  draw_minute2();
  draw_minute3();
  draw_date();
  draw_month();
  draw_year();
}

// Called once per second
void handle_minute_tick(AppContextRef ctx, PebbleTickEvent *t) {
  update_watch(t->tick_time);
}

// Handle the start-up of the app
void handle_init(AppContextRef app_ctx) {

  // Create our app's base window
  window_init(&window, "Playing Cards Watch");
  window_stack_push(&window, true);
  window_set_background_color(&window, GColorBlack);

  resource_init_current_app(&APP_RESOURCES);
	
  bmp_init_container(RESOURCE_ID_IMAGE_BACKGROUND, &background_image_container);
  layer_add_child(&window.layer, &background_image_container.layer.layer);
	
  hour1_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_ARIAL_BOLD_12));
  text_layer_init(&hour1_layer, GRect(12, 26, 20, 20));
  text_layer_set_text_alignment(&hour1_layer, GTextAlignmentCenter);
  text_layer_set_text_color(&hour1_layer, GColorBlack);
  text_layer_set_background_color(&hour1_layer, GColorClear);
  text_layer_set_font(&hour1_layer, hour1_font);
  layer_add_child(&window.layer, &hour1_layer.layer);
  draw_hour1();	

  hour2_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_ARIAL_BOLD_12));
  text_layer_init(&hour2_layer, GRect(32, 17, 20, 20));
  text_layer_set_text_alignment(&hour2_layer, GTextAlignmentCenter);
  text_layer_set_text_color(&hour2_layer, GColorBlack);
  text_layer_set_background_color(&hour2_layer, GColorClear);
  text_layer_set_font(&hour2_layer, hour2_font);
  layer_add_child(&window.layer, &hour2_layer.layer);
  draw_hour2();
	
  minute1_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_ARIAL_BOLD_12));
  text_layer_init(&minute1_layer, GRect(53, 12, 20, 20));
  text_layer_set_text_alignment(&minute1_layer, GTextAlignmentCenter);
  text_layer_set_text_color(&minute1_layer, GColorBlack);
  text_layer_set_background_color(&minute1_layer, GColorClear);
  text_layer_set_font(&minute1_layer, minute1_font);
  layer_add_child(&window.layer, &minute1_layer.layer);
  draw_minute1();	

  minute2_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_ARIAL_BOLD_12));
  text_layer_init(&minute2_layer, GRect(77, 12, 20, 20));
  text_layer_set_text_alignment(&minute2_layer, GTextAlignmentCenter);
  text_layer_set_text_color(&minute2_layer, GColorBlack);
  text_layer_set_background_color(&minute2_layer, GColorClear);
  text_layer_set_font(&minute2_layer, minute2_font);
  layer_add_child(&window.layer, &minute2_layer.layer);
  draw_minute2();	
	
  minute3_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_ARIAL_BOLD_12));
  text_layer_init(&minute3_layer, GRect(107, 90, 20, 20));
  text_layer_set_text_alignment(&minute3_layer, GTextAlignmentCenter);
  text_layer_set_text_color(&minute3_layer, GColorBlack);
  text_layer_set_background_color(&minute3_layer, GColorClear);
  text_layer_set_font(&minute3_layer, minute3_font);
  layer_add_child(&window.layer, &minute3_layer.layer);
  draw_minute3();	
				
  date_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_ARIAL_BOLD_12));
  text_layer_init(&date_layer, GRect(22, 132, 20, 20));
  text_layer_set_text_alignment(&date_layer, GTextAlignmentCenter);
  text_layer_set_text_color(&date_layer, GColorBlack);
  text_layer_set_background_color(&date_layer, GColorClear);
  text_layer_set_font(&date_layer, date_font);
  layer_add_child(&window.layer, &date_layer.layer);
  draw_date();	

  month_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_ARIAL_BOLD_12));
  text_layer_init(&month_layer, GRect(63, 127, 20, 20));
  text_layer_set_text_alignment(&month_layer, GTextAlignmentCenter);
  text_layer_set_text_color(&month_layer, GColorBlack);
  text_layer_set_background_color(&month_layer, GColorClear);
  text_layer_set_font(&month_layer, month_font);
  layer_add_child(&window.layer, &month_layer.layer);
  draw_month();
	
  year_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_ARIAL_BOLD_12));
  text_layer_init(&year_layer, GRect(103, 132, 20, 20));
  text_layer_set_text_alignment(&year_layer, GTextAlignmentCenter);
  text_layer_set_text_color(&year_layer, GColorBlack);
  text_layer_set_background_color(&year_layer, GColorClear);
  text_layer_set_font(&year_layer, year_font);
  layer_add_child(&window.layer, &year_layer.layer);
  draw_year();	
		
  PblTm t;
  get_time(&t);
  update_watch(&t);
}

void handle_deinit(AppContextRef ctx) {
  (void)ctx;

  bmp_deinit_container(&background_image_container);
 
  fonts_unload_custom_font(hour1_font);
  fonts_unload_custom_font(hour2_font);
  fonts_unload_custom_font(minute1_font);
  fonts_unload_custom_font(minute2_font);
  fonts_unload_custom_font(minute3_font);
  fonts_unload_custom_font(date_font);
  fonts_unload_custom_font(month_font);
  fonts_unload_custom_font(year_font);
}

void handle_tick(AppContextRef ctx, PebbleTickEvent *t){
  (void)t;
  (void)ctx;

   if(t->tick_time->tm_min==0&&t->tick_time->tm_hour==0)
     {
     draw_hour1();
	 draw_hour2();
     draw_minute1();
	 draw_minute2();
	 draw_minute3();
     draw_date();
     draw_month();
	 draw_year();
     }        
}

// The main event/run loop for our app
void pbl_main(void *params) {
  PebbleAppHandlers handlers = {

    // Handle app start
    .init_handler = &handle_init,
    .deinit_handler = &handle_deinit,

    // Handle time updates
    .tick_info = {
      .tick_handler = &handle_minute_tick,
      .tick_units = MINUTE_UNIT
	}
   };
  app_event_loop(params, &handlers);
}