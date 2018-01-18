<?php

/**
 * @file
 * Handles the custom panel pane for the GNE reference component.
 */

$plugin = array(
  'single' => TRUE,
  'title' => t('FCL Component - GNE reference'),
  'description' => t('Displays GNE reference value.'),
  'category' => t('FCL Components'),
  'content_types' => array('fcl_gne_reference'),
  'edit form' => 'fcc_gne_reference_panel_settings',
  'render callback' => 'fcc_gne_reference_panel_render',
  'defaults' => array(),
  'all contexts' => TRUE
);

/**
 * GNE reference edit form.
 *
 * @param $form
 * @param $form_state
 * @return mixed
 */
function fcc_gne_reference_panel_settings($form, &$form_state) {
  return $form;
}

/**
 * GNE reference form submit handler.
 *
 * @param $form
 * @param $form_state
 */
function fcc_gne_reference_panel_settings_submit($form, &$form_state) {
  foreach ($form_state['values'] as $key => $value) {
    $form_state['conf'][$key] = $value;
  }
}

/**
 * GNE reference render function.
 *
 * @param $subtype
 * @param $conf
 * @param $args
 * @param $context
 */
function fcc_gne_reference_panel_render($subtype, $conf, $args, $contexts) {
  $block = new stdClass();
  if(isset($contexts['argument_entity_id:fcl_procat_product_1'])) {
    $product = $contexts['argument_entity_id:fcl_procat_product_1']->data;
    $conf['gne_value'] = $product->gne_reference;
  }
  else {
    return NULL;
  }

  if($product->oneway_flag)
  {
    // Build the panel by constructing block.
    $block->content = array(
      '#theme' => 'gne_reference_style',
      '#config' => $conf
    );
  }
  else {
    //Return null One way airfare is not checked in product
    return NULL;
  }

  return $block;
}
