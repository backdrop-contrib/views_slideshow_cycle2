<?php
/**
 * @file
 * Integration with the Views Slideshow module.
 */

/**
 * Implements hook_views_slideshow_slideshow_info().
 */
function views_slideshow_cycle2_views_slideshow_slideshow_info() {
  return array(
    'views_slideshow_cycle2' => array(
      'name' => t('Cycle2'),
      'accepts' => array(
        'goToSlide',
        'nextSlide',
        'pause',
        'play',
        'previousSlide',
      ),
      'calls' => array(
        'transitionBegin',
        'transitionEnd',
        'goToSlide',
        'nextSlide',
        'pause',
        'play',
        'previousSlide',
      ),
    ),
  );
}

/**
 * Implements hook_views_slideshow_slideshow_type_form().
 */
function views_slideshow_cycle2_views_slideshow_slideshow_type_form(&$form, &$form_state, &$view) {
  form_load_include($form_state, 'inc', 'views_slideshow_cycle2', 'views_slideshow_cycle2.plugins');
  $default_values = $view->options['views_slideshow_cycle2'];

  // Display message if Cycle2 plugin not installed.
  $library = libraries_detect('jquery.cycle2');
  if (empty($library['installed'])) {
    $form['views_slideshow_cycle2']['no_cycle2_js'] = array(
      '#markup' => '<div style="color: red;">' . t('The Cycle2 jQuery plugin is not installed. Please refer to the Views Slideshow: Cycle2 README file for installation instructions.') . '</div>',
    );
  }

  // Transition settings.
  $form['views_slideshow_cycle2']['transition'] = array(
    '#markup' => '<h2>' . t('Transition') . '</h2>',
  );
  $plugin_effects = backdrop_map_assoc(array_keys(config_get('views_slideshow_cycle2.settings', 'plugin_effects')));
  $form['views_slideshow_cycle2']['fx'] = array(
    '#type' => 'select',
    '#title' => t('Effect'),
    '#description' => t('The transition effect used to change slides.'),
    '#options' => array(
      'none' => 'none',
      'fade' => 'fade',
      'fadeout' => 'fadeout',
      'scrollHorz' => 'scrollHorz',
    ) + $plugin_effects,
    '#default_value' => $default_values['fx'],
  );

  // Transition effect options.
  // Create array of all options-enabled effects.
  $plugins = views_slideshow_cycle2_supported_plugins();
  $conditions = array();
  foreach ($plugins as $plugin) {
    if (!empty($plugin['options'])) {
      foreach ($plugin['effects'] as $effect) {
        $conditions[]['value'] = $effect;
      }
    }
  }
  $form['views_slideshow_cycle2']['effect_options'] = array(
    '#type' => 'fieldset',
    '#title' => t('Effect options'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#states' => array(
      'visible' => array(
        ':input[name$="[views_slideshow_cycle2][fx]"]' => $conditions,
      ),
    ),
  );
  foreach ($plugins as $plugin => $plugin_info) {
    if (!empty($plugin_info['options'])) {
      // Create array of this plugin's effects.
      $conditions = array();
      foreach ($plugin_info['effects'] as $effect) {
        $conditions[]['value'] = $effect;
      }
      $form['views_slideshow_cycle2']['effect_options'][$plugin] = array(
        '#type' => 'container',
        '#states' => array(
          'visible' => array(
            ':input[name$="[views_slideshow_cycle2][fx]"]' => $conditions,
          ),
        ),
      );

      // Get form options from plugin.
      call_user_func_array($plugin_info['options'], array(
        &$form['views_slideshow_cycle2']['effect_options'][$plugin],
        $default_values,
      ));
    }
  }

  $form['views_slideshow_cycle2']['timeout'] = array(
    '#type' => 'number',
    '#title' => t('Slide interval'),
    '#description' => t("Amount of time, in milliseconds, each slide is shown for. Set to '0' to disable the slideshow (slides must be transitioned manually)."),
    '#default_value' => $default_values['timeout'],
    '#min' => 0,
    '#max' => 99999,
  );
  $form['views_slideshow_cycle2']['speed'] = array(
    '#type' => 'number',
    '#title' => t('Transition speed'),
    '#description' => t('The speed, in milliseconds, of the transition effect.'),
    '#default_value' => $default_values['speed'],
    '#min' => 1,
    '#max' => 99999,
  );

  // Transition advanced options.
  $form['views_slideshow_cycle2']['transition_advanced'] = array(
    '#type' => 'fieldset',
    '#title' => t('Transition advanced options'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['views_slideshow_cycle2']['transition_advanced']['delay'] = array(
    '#type' => 'number',
    '#title' => t('Initial delay'),
    '#description' => t("Amount of time, in milliseconds, to add onto or substract from the first slide's interval."),
    '#default_value' => $default_values['delay'],
    '#min' => 0,
    '#max' => 99999,
  );
  $form['views_slideshow_cycle2']['transition_advanced']['sync'] = array(
    '#type' => 'checkbox',
    '#title' => t('Synchronize transitions'),
    '#description' => t('When enabled, the transition effect of the incoming and outgoing slides will be synchronized. When disabled, the transition effect for the incoming slide will not start until the transition effect for the outgoing slide completes.'),
    '#default_value' => $default_values['sync'],
  );
  $form['views_slideshow_cycle2']['transition_advanced']['swipe'] = array(
    '#type' => 'checkbox',
    '#title' => t('Swipe gesture support'),
    '#description' => t('Enable swipe gesture support for advancing the slideshow forward or back on mobile devices.'),
    '#default_value' => $default_values['swipe'],
  );

  // Action settings.
  $form['views_slideshow_cycle2']['action'] = array(
    '#markup' => '<h2>' . t('Action') . '</h2>',
  );
  $form['views_slideshow_cycle2']['pause-on-hover'] = array(
    '#type' => 'checkbox',
    '#title' => t('Pause on hover'),
    '#description' => t('Pause an auto-running slideshow while the mouse is over the slideshow.'),
    '#default_value' => $default_values['pause-on-hover'],
  );

  // Action advanced options.
  $form['views_slideshow_cycle2']['action_advanced'] = array(
    '#type' => 'fieldset',
    '#title' => t('Action advanced options'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['views_slideshow_cycle2']['action_advanced']['allow-wrap'] = array(
    '#type' => 'checkbox',
    '#title' => t('Loop slideshow'),
    '#description' => t('When enabled, the slideshow will loop back to the first slide after showing the last one (and vice versa). When disabled, the slideshow will stop after the last slide.'),
    '#default_value' => $default_values['allow-wrap'],
  );
  $form['views_slideshow_cycle2']['action_advanced']['paused'] = array(
    '#type' => 'checkbox',
    '#title' => t('Begin paused'),
    '#description' => t('Begin the slideshow in a paused state.'),
    '#default_value' => $default_values['paused'],
  );
  $form['views_slideshow_cycle2']['action_advanced']['auto-height'] = array(
    '#type' => 'select',
    '#title' => t('Auto height'),
    '#description' => t("The method used to determine and manage the height of the slideshow.<br><strong>Disabled:</strong> Disable height management (use CSS to manually set the height of your slideshow).<br><strong>First slide:</strong> The height of the first slide determines the height of the slideshow.<br><strong>Tallest slide:</strong> The height of the tallest slide determines the height of the slideshow.<br><strong>Dynamic:</strong> The height of the slideshow changes depending on the height of the current slide."),
    '#options' => array(
      'false' => t('Disabled'),
      '0' => t('First slide'),
      'calc' => t('Tallest slide'),
      'container' => t('Dynamic'),
    ),
    '#default_value' => $default_values['auto-height'],
  );
  $form['views_slideshow_cycle2']['action_advanced']['loader'] = array(
    '#type' => 'select',
    '#title' => t('Image loader'),
    '#description' => t('Set the image loader behavior for the slideshow.<br><strong>Wait:</strong> Wait for all images to load before starting the slideshow.<br><strong>Quick:</strong> Show slides as individual images load. NOTE: Slides may appear out of order.'),
    '#options' => array(
      'false' => t('None'),
      'wait' => t('Wait'),
      'true' => t('Quick'),
    ),
    '#default_value' => $default_values['loader'],
  );
}

/**
 * Implements hook_views_slideshow_options_form_submit().
 *
 * Flatten form values array.
 */
function views_slideshow_cycle2_views_slideshow_options_form_submit($form, &$form_state) {
  $options = &$form_state['values']['style_options']['views_slideshow_cycle2'];

  // Transition effect options.
  foreach ($options['effect_options'] as $plugin) {
    foreach ($plugin as $key => $value) {
      $options[$key] = $value;
    }
  }
  unset($options['effect_options']);

  // Transition advanced options.
  foreach ($options['transition_advanced'] as $key => $value) {
    $options[$key] = $value;
  }
  unset($options['transition_advanced']);

  // Action advanced options.
  foreach ($options['action_advanced'] as $key => $value) {
    $options[$key] = $value;
  }
  unset($options['action_advanced']);
}

/**
 * Implements hook_views_slideshow_option_definition().
 */
function views_slideshow_cycle2_views_slideshow_option_definition() {
  return array(
    'views_slideshow_cycle2' => array(
      'contains' => array(
        'fx' => array('default' => 'fade'),

        // Effect options.
        'carousel-vertical' => array('default' => 'false'),
        'carousel-visible' => array('default' => NULL),
        'carousel-fluid' => array('default' => FALSE),
        'shuffle-left' => array('default' => 0),
        'shuffle-right' => array('default' => 0),
        'shuffle-top' => array('default' => 15),
        'tile-vertical' => array('default' => 'true'),
        'tile-count' => array('default' => 7),
        'tile-delay' => array('default' => 100),

        // Transition.
        'timeout' => array('default' => 4000),
        'speed' => array('default' => 500),
        'delay' => array('default' => 0),
        'sync' => array('default' => TRUE),
        'swipe' => array('default' => FALSE),

        // Action.
        'pause-on-hover' => array('default' => FALSE),
        'allow-wrap' => array('default' => TRUE),
        'paused' => array('default' => FALSE),
        'auto-height' => array('default' => '0'),
        'loader' => array('default' => 'false'),
      ),
    ),
  );
}

