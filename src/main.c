#include <pebble.h>
#include <catch.h>
  
#define NUM_MENU_SECTIONS 1  
#define NUM_MENU_ITEMS 3
  
Window *window1;
Layer *basic_layer;
TextLayer *text_layer;
static Window *s_main_window;
static MenuLayer *s_menu_layer;
static GBitmap *s_menu_bitmap1;
static GBitmap *s_menu_bitmap2;
static GBitmap *s_menu_bitmap3;

// 4/17 Kim's Code:
static catch_t catch_obj;
static void in_received_handler(DictionaryIterator *iter, void *context)
{
  //How to process received Tuples.
  (void) context;
     
    //Get data
    //Read first item
    Tuple *t = dict_read_first(iter);
    //Repeat reading until no more returned
    while(t != NULL)
    {
        // switch based process_tuple() fn to spearate out the process
        int key = t->key;
        int value = t->value->int32;
        t = dict_read_next(iter);
    }
}
// -----------------------------------------------------------------------------------

static uint16_t menu_get_num_sections_callback(MenuLayer *menu_layer, void *data) {
  return NUM_MENU_SECTIONS;
}

static uint16_t menu_get_num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) {
  return NUM_MENU_ITEMS;
}

static int16_t menu_get_header_height_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) {
  return MENU_CELL_BASIC_HEADER_HEIGHT;
}

static void menu_draw_header_callback(GContext* ctx, const Layer *cell_layer, uint16_t section_index, void *data) {
      menu_cell_basic_header_draw(ctx, cell_layer, "Menu");
}

static void menu_draw_row_callback(GContext* ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data) {
  // Determine which section we're going to draw in
  switch (cell_index->section) {
    case 0:
      switch (cell_index->row) {
        case 0:
          // This is a basic menu item with a title and subtitle
          menu_cell_basic_draw(ctx, cell_layer, "Challenge", NULL, s_menu_bitmap1);
          break;
        case 1:
          // This is a basic menu icon with a cycling icon
          menu_cell_basic_draw(ctx, cell_layer, "FEED",NULL, s_menu_bitmap2);
          break;
        case 2: 
          menu_cell_basic_draw(ctx, cell_layer, "Catch", NULL, s_menu_bitmap3);
          break;
      }
    break;
  }  
}

static void main_window_load(Window *window) { 
  // load the bitmap assets
  s_menu_bitmap1=gbitmap_create_with_resource(RESOURCE_ID_IMAGE_MENU_ICON_CHALLENGE1);
  s_menu_bitmap2=gbitmap_create_with_resource(RESOURCE_ID_IMAGE_MENU_ICON_FEED1);
  s_menu_bitmap3=gbitmap_create_with_resource(RESOURCE_ID_IMAGE_MENU_ICON_CATCH1);
  // load the background

  // prepare to initialize the menu layer
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_frame(window_layer);

  // Create the menu layer
  s_menu_layer = menu_layer_create(bounds);
  menu_layer_set_callbacks(s_menu_layer, NULL, (MenuLayerCallbacks){
    .get_num_sections = menu_get_num_sections_callback,
    .get_num_rows = menu_get_num_rows_callback,
    .get_header_height = menu_get_header_height_callback,
    .draw_header = menu_draw_header_callback,
    .draw_row = menu_draw_row_callback,
  });

  // Bind the menu layer's click config provider to the window for interactivity
  menu_layer_set_click_config_onto_window(s_menu_layer, window);

  layer_add_child(window_layer, menu_layer_get_layer(s_menu_layer));
}

static void main_window_unload(Window *window) {
  // Destroy the menu layer
  menu_layer_destroy(s_menu_layer);
}

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
 //if(window1==1){
  s_main_window = window_create();
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload,
  });
  window_stack_push(s_main_window, true);
}

// 4/17 Kim's Code:
void down_click_handler(ClickRecognizerRef recognizer, void *context)
{
      catch_speak(&catch_obj, text_layer);
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  
  // 4/17 Kim's Code:
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

void basic_update_proc(Layer*l,GContext *ctx){
  graphics_context_set_text_color(ctx,GColorBlack);
  graphics_draw_rect(ctx,GRect(32,61,80,30));
}

void init(){
  window1=window_create();
  Layer *window_layer=window_get_root_layer(window1);
  text_layer=text_layer_create(GRect(32,60,100,100));
  text_layer_set_font(text_layer,fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
  text_layer_set_text(text_layer,"*Swabe*");
  layer_add_child(window_layer,text_layer_get_layer(text_layer));
  basic_layer=layer_create(GRect(0,0,144,168));
 // layer_set_update_proc(basic_layer,basic_update_proc);
  layer_add_child(window_layer,basic_layer); 
  //window_stack_push(window1,true);
  window_set_click_config_provider(window1, click_config_provider);
  
  // 4/14 Kim's Edit Code:
  /* Initialize catch object */
  catch_init(&catch_obj);
  /*WindowHandlers handlers = {
    .load = main_window_load,
    .unload = main_window_unload
  };
  window_set_window_handlers(window1, handlers);
  app_message_register_inbox_received(in_received_handler);
  app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());*/
  window_stack_push(window1, true);
}

static void deinit() {
  // Destroy Window
  window_destroy(window1);
  window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}