<?php

import('lib.pkp.classes.plugins.GenericPlugin');

class ReviewFileAdderPlugin extends GenericPlugin
{

    function register($category, $path, $mainContextId = null) {
        if (parent::register($category, $path, $mainContextId)) {
            if ($this->getEnabled($mainContextId)) {

                HookRegistry::register('reviewerreviewstep3form::validate',array($this, 'addFileCallback'));

            }
            return true;
        }
        return false;
    }

    function addFileCallback($hookName, $args){
        foreach ($args as $k) {
            error_log($k);
        }
    }

    function getDisplayName()
    {
        return 'ReviewFileAdder';
    }

    function getDescription()
    {
        return 'Automatically inserts review form as a file';
    }


}