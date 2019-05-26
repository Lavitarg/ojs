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
        error_log("Hook catched! Length: " . (count($args)));
        foreach ($args as $s) {
            error_log(gettype($s));
        }
        $myRequest = Application::get()->getRequest();
        error_log(gettype($myRequest->getUserVar($args[0])));
        error_log((strval($myRequest->getUserVar($args[0]))));
        error_log($myRequest->getUserVar($args[0]));



        return true;


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