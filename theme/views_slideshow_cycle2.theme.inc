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
  $plugins = array(
    'scrollVert' => 'scrollVert',
    'carousel' => 'carousel',
    'flipHorz' => 'flip',
    'flipVert' => 'flip',
    'shuffle' => 'shuffle',
    'tileSlide' => 'tile',
    'tileBlind' => 'tile',
  );

  // Add the necessary Cycle2 library files, exit if unsuccessful.
  $cycle2_added = $plugin_added = $swipe_added = $center_added = TRUE;
  $cycle2_added = backdrop_add_library('views_slideshow_cycle2', 'cycle2');
  if (!empty($plugins[$settings['fx']])) {
    $plugin_added = backdrop_add_library('views_slideshow_cycle2', 'cycle2.' . $plugins[$settings['fx']]);
  }
  if ($settings['swipe']) {
    $swipe_added = backdrop_add_library('views_slideshow_cycle2', 'cycle2.swipe');
  }
  if ($settings['center-horz'] || $settings['center-vert']) {
    $center_added = backdrop_add_library('views_slideshow_cycle2', 'cycle2.center');
  }
  if (!$cycle2_added || !$plugin_added || !$swipe_added) {
    return;
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
  $vars['classes'][] = 'cycle-slideshow';
  $vars['classes'][] = 'views-slideshow-cycle2-main-frame';

  // Get slides.
  $vars['rendered_rows'] = '';
  $total = count($vars['rows']);
  foreach ($vars['rows'] as $key => $row) {
    $vars['rendered_rows'] .= theme(views_theme_functions('views_slideshow_cycle2_main_frame_slide', $vars['view'], $vars['view']->display[$vars['view']->current_display]), array(
      'fields' => $row,
      'key' => $key,
      'total' => $total,
      'options' => $vars['options'],
      'views_style_plugin' => $vars['view']->style_plugin,
    ));
  }
}

/**
 * Theme a slideshow slide.
 *
 * @ingroup themeable
 */
function template_preprocess_views_slideshow_cycle2_main_frame_slide(&$vars) {
  $count = $vars['key'] + 1;

  // Add custom classes.
  $vars['classes'][] = 'views-slideshow-cycle2-slide';
  $vars['classes'][] = 'views-slideshow-slide';

  // Add views classes.
  if ($vars['options']['default_row_class']) {
    $vars['classes'][] = 'views-row';
    $vars['classes'][] = 'views-row-' . $count;
  }
  if ($vars['options']['row_class_special']) {
    $vars['classes'][] = ($count % 2) ? 'odd' : 'even';
    if ($count == 1) {
      $vars['classes'][] = 'first';
    }
    if ($count == $vars['total']) {
      $vars['classes'][] = 'last';
    }
  }
  if ($row_class = $vars['views_style_plugin']->get_row_class($vars['key'])) {
    $vars['classes'][] = $row_class;
  }
}
