<?php
/**
 * @file
 * Theme & preprocess functions for the Views Slideshow: Cycle2 module.
 */

/**
 * Theme the slideshow main frame.
 *
 * @ingroup themeable
 */
function template_preprocess_views_slideshow_cycle2_main_frame(&$vars) {
  $settings = $vars['settings'];
  $vss_id = $vars['vss_id'];

  // Load the Cycle2 library files, exit if unsuccessful.
  $library = libraries_load('jquery.cycle2');
  if (!$library['loaded']) {
    return;
  }

  // Load our custom CSS.
  //backdrop_add_css(backdrop_get_path('module', 'views_slideshow_cycle2') . '/views_slideshow_cycle2.css', 'file');

  // Clean up settings.
  foreach ($settings as $key => &$value) {
    if (is_string($value)) {
      $value = trim(str_replace("\n", ' ', $value));

      if (is_numeric($value)) {
        $value = (int) $value;
      }
      elseif (strtolower($value) == 'true') {
        $value = TRUE;
      }
      elseif (strtolower($value) == 'false') {
        $value = FALSE;
      }
    }
  }

  // Add hard-coded settings.
  $settings['log'] = FALSE;
  $settings['next'] = '#views_slideshow_controls_text_' . $vss_id . ' .views-slideshow-controls-text-next';
  $settings['pager'] = '#widget_pager_top_' . $vss_id . ', #widget_pager_bottom_' . $vss_id;
  $settings['pager-template'] = '';
  $settings['prev'] = '#views_slideshow_controls_text_' . $vss_id . ' .views-slideshow-controls-text-previous';
  $settings['slides'] = '> .views-slideshow-cycle2-slide';

  // Setup data attributes.
  $vars['data_attr'] = '';
  foreach ($settings as $key => $value) {
    if (is_bool($value)) {
      $value = ($value) ? 'true' : 'false';
    }
    $vars['data_attr'] .= ' data-cycle-' . $key . '="' . $value . '"';
  }

  // Initialize Cycle2 with a class.
  $vars['classes_array'][] = 'cycle-slideshow';
  $vars['classes_array'][] = 'views-slideshow-cycle2-main-frame';

  // Get slides.
  $vars['rendered_rows'] = '';
  $total = count($vars['rows']);
  foreach ($vars['rows'] as $key => $row) {
    $vars['rendered_rows'] .= theme(views_theme_functions('views_slideshow_cycle2_main_frame_slide', $vars['view'], $vars['view']->display[$vars['view']->current_display]), array('fields' => $row, 'key' => $key, 'total' => $total, 'options' => $vars['options'], 'views_style_plugin' => $vars['view']->style_plugin));
  }

  /*$data_attributes = array(
    'allow-wrap' => $settings['nowrap'] == 0 ? TRUE : FALSE,
    'delay' => $settings['delay'],
    'fx' => $settings['effect'],
    'pause-on-hover' => $settings['pause'] == 0 ? FALSE : TRUE,
    'random' => $settings['random'] == 0 ? FALSE : TRUE,
    'speed' => $settings['speed'],
    'swipe' => $settings['swipe'] == 0 ? FALSE : TRUE,
    'timeout' => $settings['timeout'],
    'loader' => $settings['image_loader'],
    'log' => FALSE,
    'pager' => '#widget_pager_bottom_' . $vss_id . ', #widget_pager_top_' . $vss_id,
    'pager-template' => '',
    'prev' => '#views_slideshow_controls_text_' . $vss_id . ' .views-slideshow-controls-text-previous',
    'next' => '#views_slideshow_controls_text_' . $vss_id . ' .views-slideshow-controls-text-next',
    'slides' => '> .views_slideshow_slide',
  );

  // Implement effect-specific options.
  preg_match('/[a-z]+/', $settings['fx'], $effect_base);
  if (isset($settings['effect_options'][$effect_base[0]])) {
    foreach ($settings['effect_options'][$effect_base[0]] as $key => $value) {
      $data_attributes[$key] = $value;
    }
  }*/

  $vars['classes'] = implode(' ', $vars['classes_array']);
}

/**
 * Theme a slideshow slide.
 *
 * @ingroup themeable
 */
function template_preprocess_views_slideshow_cycle2_main_frame_slide(&$vars) {
  $count = $vars['key'] + 1;

  // Add custom classes.
  $vars['classes_array'][] = 'views-slideshow-cycle2-slide';
  $vars['classes_array'][] = 'views-slideshow-slide';

  // Add views classes.
  if ($vars['options']['default_row_class']) {
    $vars['classes_array'][] = 'views-row';
    $vars['classes_array'][] = 'views-row-' . $count;
  }
  if ($vars['options']['row_class_special']) {
    $vars['classes_array'][] = ($count % 2) ? 'odd' : 'even';
    if ($count == 1) {
      $vars['classes_array'][] = 'first';
    }
    if ($count == $vars['total']) {
      $vars['classes_array'][] = 'last';
    }
  }
  if ($row_class = $vars['views_style_plugin']->get_row_class($vars['key'])) {
    $vars['classes_array'][] = $row_class;
  }

  $vars['classes'] = implode(' ', $vars['classes_array']);
}

/**
* Theme the main frame wrapper.
*
* @ingroup themeable
*/
/*function template_preprocess_views_slideshow_cycle2_main_frame(&$vars) {
 $settings = $vars['settings'];
 $vss_id = $vars['vss_id'];

 // Load the Cycle2 library files, exit if unsuccessful.
 $library = libraries_load('jquery.cycle2');
 if (!$library['loaded']) {
   return;
 }

 // Load our custom CSS.
 backdrop_add_css(backdrop_get_path('module', 'views_slideshow_cycle2') . '/views_slideshow_cycle2.css', 'file');

 // Clean up settings.
 foreach ($settings as $key => &$value) {
   if (is_string($value)) {
     $value = trim(str_replace("\n", ' ', $value));

     if (is_numeric($value)) {
       $value = (int) $value;
     }
     elseif (strtolower($value) == 'true') {
       $value = TRUE;
     }
     elseif (strtolower($value) == 'false') {
       $value = FALSE;
     }
   }
 }
 $settings['vss_id'] = $vss_id;
 dpm($settings);

 // Initialize Cycle2 with a class.
 $vars['classes'][] = 'cycle-slideshow';

 // Get slides.
 dpm($vars['rows']);
 dpm($vars['rendered_rows'] = theme(views_theme_functions('views_slideshow_cycle2_main_frame_row', $vars['view'], $vars['view']->display[$vars['view']->current_display]), array('vss_id' => $vss_id, 'items' => $vars['rows'], 'view' => $vars['view'])));

 $data_attributes = array(
   'allow-wrap' => $settings['nowrap'] == 0 ? TRUE : FALSE,
   'delay' => $settings['delay'],
   'fx' => $settings['effect'],
   'pause-on-hover' => $settings['pause'] == 0 ? FALSE : TRUE,
   'random' => $settings['random'] == 0 ? FALSE : TRUE,
   'speed' => $settings['speed'],
   'swipe' => $settings['swipe'] == 0 ? FALSE : TRUE,
   'timeout' => $settings['timeout'],
   'loader' => $settings['image_loader'],
   'log' => FALSE,
   'pager' => '#widget_pager_bottom_' . $vss_id . ', #widget_pager_top_' . $vss_id,
   'pager-template' => '',
   'prev' => '#views_slideshow_controls_text_' . $vss_id . ' .views-slideshow-controls-text-previous',
   'next' => '#views_slideshow_controls_text_' . $vss_id . ' .views-slideshow-controls-text-next',
   'slides' => '> .views_slideshow_slide',
 );

 // Implement effect-specific options.
 preg_match('/[a-z]+/', $settings['fx'], $effect_base);
 if (isset($settings['effect_options'][$effect_base[0]])) {
   foreach ($settings['effect_options'][$effect_base[0]] as $key => $value) {
     $data_attributes[$key] = $value;
   }
 }

 $vars['data_attr'] = '';
 foreach ($data_attributes as $key => $value) {
   if ($value === TRUE || $value === FALSE) {
     $value = ($value) ? 'true' : 'false';
     $vars['data_attr'] .= " data-cycle-$key=$value";
   }
   else {
     $vars['data_attr'] .= " data-cycle-$key=\"$value\"";
   }
 }
}*/

/**
* Views Slideshow slideshow rows.
*
* @ingroup themeable
*/
/*function template_preprocess_views_slideshow_cycle2_main_frame_row(&$vars) {
 $vars['classes'][] = 'views_slideshow_cycle2_slide';

 $vars['rendered_items'] = '';
 foreach ($vars['items'] as $item_count => $item) {
   $vars['rendered_items'] .= theme(views_theme_functions('views_slideshow_cycle2_main_frame_row_item', $vars['view'], $vars['view']->display[$vars['view']->current_display]), array('item' => $item, 'item_count' => $item_count, 'view' => $vars['view']));
 }
}*/

/*function template_preprocess_views_slideshow_cycle2_main_frame_row_item(&$vars) {
 $vars['classes'][] = 'views-row views-row-' . $vars['item_count'];
 if (!$vars['item_count']) {
   $vars['classes'][] = 'views-row-first';
 }
 if ($vars['item_count'] % 2) {
   $vars['classes'][] = 'views-row-even';
 }
 else {
   $vars['classes'][] = 'views-row-odd';
 }
}*/
