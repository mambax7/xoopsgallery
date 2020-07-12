{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
{assign var="lowercase" value=$lowercase|default:false}
{* if we have more than one link, use a dropdown if $useDropdown is set *}
{* one link, just show it as a link *}
{if (isset($links) || isset($theme.itemLinks))}
  {if empty($item)}{assign var="item" value=$theme.item}{/if}
  {if !isset($links)}{assign var="links" value=$theme.itemLinks}{/if}
  {if !isset($useDropdown)}{assign var="useDropdown" value=true}{/if}

  {if $useDropdown && count($links) > 1}
      <div class="{$class}">
       <select onchange="{literal}if (this.value) { newLocation = this.value; this.options[0].selected = true; location.href= newLocation; }{/literal}">
        <option label="{if $item.canContainChildren}{g->text text="&laquo; album actions &raquo;"}{else}{g->text text="&laquo; item actions &raquo;"}{/if}" value="">
        {if $item.canContainChildren}{g->text text="&laquo; album actions &raquo;"}{else}{g->text text="&laquo; item actions &raquo;"}{/if}</option>
         {foreach from=$links item=link}
	       {if $lowercase}{assign var="linkText" value=$link.text|lower}{else}
		       			{assign var="linkText" value=$link.text}{/if}
	       <option label="{$linkText}" value="{g->url params=$link.params}">{$linkText}</option>
        {/foreach}
       </select>
      </div>
    {elseif count($links) > 0}
      <div class="{$class}">
        {foreach from=$links item=link}
          <a href="{g->url params=$link.params}" class="giInfo {g->linkId urlParams=$link.params}">
			{if $lowercase}{$link.text|lower}{else}{$link.text}{/if}</a>
        {/foreach}
        {* <br> 
        <a class="giInfo" href="{g->url arg1="view=cart.ViewCart"}">{g->text text=" View Cart"} {g->callback type="cart.LoadCart"}{g->text one=" (%d item)" many=" (%d items)"
             count=$block.cart.ShowCart.total arg1=$block.cart.ShowCart.total} </a> *}
      </div>
    {/if}

  {/if}
  {if isset($ItemAdmin)}
       <div class="{$class}">
		{if empty($ItemAdmin.thumbnail)}
	 		{g->text text="No Thumbnail"}
		{else}
	  		{g->image item=$ItemAdmin.item image=$ItemAdmin.thumbnail maxSize=130}
	    {/if}
	   <br /><b>{$ItemAdmin.item.title|markup}</b><br />
       </div>
   
	<div class="{$class}">	
	  {foreach from=$ItemAdmin.subViewChoices key=choiceName item=choiceParams}
	    {if isset($choiceParams.active)} <a href="{g->url params=$choiceParams}" class="gbAdminLink {g->linkId urlParams=$choiceParams}"><font color="black"> {$choiceName}</font> </a>
		{else}<a href="{g->url params=$choiceParams}" class="gbAdminLink {g->linkId urlParams=$choiceParams}"> {$choiceName} </a>{/if}	   
	  {/foreach}
 	</div>
  {/if}
  {if isset($SiteAdmin)}
   <div class="{$class}">
		
	  {foreach from=$SiteAdmin.subViewGroups item=group}
	  <h2>{$group.0.groupLabel}</h2>
	  
	    {foreach from=$group item=choice}
		<div style="padding-left:2em">
		 {if ($SiteAdmin.subViewName == $choice.view)}
		  <a href="{g->url arg1="view=core.SiteAdmin" arg2="subView=`$choice.view`"}" class="gbAdminLink {g->linkId urlParams=$choice}">
		    <font color="black"> {$choice.name} </font>
		  </a>
		  {else}
		  <a href="{g->url arg1="view=core.SiteAdmin" arg2="subView=`$choice.view`"}" class="gbAdminLink {g->linkId urlParams=$choice}">
		    {$choice.name}
		  </a>
		  {/if}
		 </div>
	    {/foreach}
	  
	 
	  {/foreach}
	  
    {/if}
 