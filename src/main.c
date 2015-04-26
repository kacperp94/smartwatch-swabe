#include <pebble.h>
  
#define NUM_MENU_SECTIONS 1  
#define NUM_MENU_ITEMS 3
static Window *s_main_window;
// static Window*start_window1;
// static Layer *basic_layer;
// static TextLayer *text_layer;
static MenuLayer *s_menu_layer;
static GBitmap *s_menu_bitmap1;
static GBitmap *s_menu_bitmap2;
static GBitmap *s_menu_bitmap3;

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
      menu_cell_basic_header_draw(ctx, cell_layer, "FOOD");
}

static void menu_draw_row_callback(GContext* ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data) {
  // Determine which section we're going to draw in
  switch (cell_index->section) {
    case 0:
      switch (cell_index->row) {
        case 0:
          // This is a basic menu item with a title and subtitle
          menu_cell_basic_draw(ctx, cell_layer, "Aluminum", "makes me stronger!", s_menu_bitmap1);
          break;
        case 1:
          // This is a basic menu icon with a cycling icon
          menu_cell_basic_draw(ctx, cell_layer, "Hydrogen","gives me energy!", s_menu_bitmap2);
          break;
        case 2: 
          menu_cell_basic_draw(ctx, cell_layer, "Oxygen","keeps me alive!", s_menu_bitmap3);
          break;
      }
    break;
  }  
}

static void main_window_load(Window *window) {
  // Here we load the bitmap assets
  s_menu_bitmap1=gbitmap_create_with_resource(RESOURCE_ID_IMAGE_MENU_ICON_Aluminum);
  s_menu_bitmap2=gbitmap_create_with_resource(RESOURCE_ID_IMAGE_MENU_ICON_Hydrogen);
  s_menu_bitmap3=gbitmap_create_with_resource(RESOURCE_ID_IMAGE_MENU_ICON_Oxygen);

  // And also load the background
  //s_background_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BACKGROUND_HEART1);

  // Now we prepare to initialize the menu layer
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

static void init() {
  s_main_window = window_create();
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload,
  });
  window_stack_push(s_main_window, true);
}
static void deinit() {
  window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
