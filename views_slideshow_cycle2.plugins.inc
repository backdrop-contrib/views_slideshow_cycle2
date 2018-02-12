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
 *   function that provides form items for setting the plugin's options).
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
  $form['carousel-vertical'] = array(
    '#type' => 'select',
    '#title' => t('Direction'),
    '#options' => array(
      'false' => t('Horizontal'),
      'true' => t('Vertical'),
    ),
    '#default_value' => $default_values['carousel-vertical'],
  );
  $form['carousel-visible'] = array(
    '#type' => 'number',
    '#title' => t('Number of slides'),
    '#description' => t("Number of slides to be displayed in the carousel. Leave empty to display as many slides as can fit in the slideshow container. Setting this option will cause the carousel to have a fixed width unless 'Responsive' is set below."),
    '#default_value' => $default_values['carousel-visible'],
    '#min' => 1,
    '#max' => 999,
  );
  $form['carousel-fluid'] = array(
    '#type' => 'checkbox',
    '#title' => t('Responsive'),
    '#description' => t("If this is enabled and 'Number of slides' is set, then the slides within the carousel will be resized in order to fill the container with the number of slides specified above."),
    '#default_value' => $default_values['carousel-fluid'],
    '#states' => array(
      'visible' => array(
        ':input[name$="[carousel][carousel-visible]"]' => array('!value' => ''),
      ),
    ),
  );
}

/**
 * Provide form options for the Shuffle plugin.
 */
function _shuffle_options(&$form, $default_values) {
  $form['shuffle-left'] = array(
    '#type' => 'number',
    '#title' => t('Left position'),
    '#description' => t("Number of pixels relative to the container's left edge to move the slide when transitioning. Set to negative to move beyond the container's left edge."),
    '#default_value' => $default_values['shuffle-left'],
    '#min' => -9999,
    '#max' => 9999,
  );
  $form['shuffle-right'] = array(
    '#type' => 'number',
    '#title' => t('Right position'),
    '#description' => t("Number of pixels relative to the container's right edge to move the slide when transitioning. Set to negative to move beyond the container's right edge. If 'Left position' is set above, this value will be ignored."),
    '#default_value' => $default_values['shuffle-right'],
    '#min' => -9999,
    '#max' => 9999,
  );
  $form['shuffle-top'] = array(
    '#type' => 'number',
    '#title' => t('Vertical position'),
    '#description' => t("Number of pixels to shuffle in a vertical direction. A positive number indicates shuffling the slide downward and a negative number indicates shuffling upward."),
    '#default_value' => $default_values['shuffle-top'],
    '#min' => -9999,
    '#max' => 9999,
  );
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

