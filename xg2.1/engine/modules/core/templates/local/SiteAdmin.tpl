{*
 * $Revision: 1.43 $
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<form action="{g->url}" method="post" id="siteAdminForm"
      enctype="{$SiteAdmin.enctype|default:"application/x-www-form-urlencoded"}">
  <div>
    {g->hiddenFormVars}
    <input type="hidden" name="{g->formVar var="controller"}" value="{$controller}"/>
    <input type="hidden" name="{g->formVar var="form[formName]"}" value="{$form.formName}" />
  </div>

  <table width="100%" cellspacing="0" cellpadding="0">
    <tr valign="top">
    <td id="gsSidebarCol"><div id="gsSidebar" class="gcBorder1">
     </td>

    <td>
      <div id="gsContent" class="gcBorder1">
	{include file="gallery:`$SiteAdmin.viewBodyFile`" l10Domain=$SiteAdmin.viewL10Domain}
      </div> 
    </td>
  </tr></table>
</form>
