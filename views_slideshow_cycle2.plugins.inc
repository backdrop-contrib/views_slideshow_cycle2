<?php
/**
 * @file
 * Provide a list of supported plugins and their options.
 */

/**
 * Get supported transition plugins.
 *
 * @return array
 *   An array of supported transition plugins keyed by the plugin name (based
 *   off the filename: e.g. 'jquery.cycle2.[NAME].min.js'). The value includes
 *   'effects' (an array of provided transition effects) and 'options' (a
 *   function that provides form items for setting the plugin's options and
 *   which takes the form's default values as an argument).
 */
function views_slideshow_cycle2_supported_plugins() {
  return array(
    'carousel' => array(
      'effects' => array(
        'carousel',
      ),
      'options' => '_carousel_options',
    ),
    'flip' => array(
      'effects' => array(
        'flipHorz',
        'flipVert',
      ),
    ),
    'scrollVert' => array(
      'effects' => array(
        'scrollVert',
      ),
    ),
    'shuffle' => array(
      'effects' => array(
        'shuffle',
      ),
      'options' => '_shuffle_options',
    ),
    'tile' => array(
      'effects' => array(
        'tileSlide',
        'tileBlind',
      ),
      'options' => '_tile_options',
    ),
  );
}

/**
 * Provide form options for the Carousel plugin.
 */
function _carousel_options(&$form, $default_values) {

}

/**
 * Provide form options for the Shuffle plugin.
 */
function _shuffle_options(&$form, $default_values) {

}

/**
 * Provide form options for the Tile plugin.
 */
function _tile_options(&$form, $default_values) {
  $form['tile-vertical'] = array(
    '#type' => 'select',
    '#title' => t('Direction'),
    '#options' => array(
      'true' => t('Vertical'),
      'false' => t('Horizontal'),
    ),
    '#default_value' => $default_values['tile-vertical'],
  );
  $form['tile-count'] = array(
    '#type' => 'number',
    '#title' => t('Tile count'),
    '#description' => t('The number of tiles to use in the transition.'),
    '#default_value' => $default_values['tile-count'],
    '#min' => 1,
    '#max' => 99,
  );
  $form['tile-delay'] = array(
    '#type' => 'number',
    '#title' => t('Tile delay'),
    '#description' => t('The number of milliseconds to delay each individual tile transition.'),
    '#default_value' => $default_values['tile-delay'],
    '#min' => 1,
    '#max' => 9999,
  );
}

