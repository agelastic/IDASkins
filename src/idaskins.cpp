/**
 * This file is part of IDASkins IDA PRO plugin (zyantific.com).
 * 
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 Joel H�ner (athre0z)
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy, modify, merge, publish, 
 * distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the 
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all copies or 
 * substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING 
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "Utils.hpp"
#include "Settings.hpp"

#include "PluginConfig.hpp"
#include "Core.hpp"

#include <QtGui>
#include <QDockWidget>
//#include <config.hpp>
#include <ida.hpp>
#include <idp.hpp>
#include <loader.hpp>
#include <diskio.hpp>
#include <functional>

 // ============================================================================================= //

/**
 * @brief   Initialization callback for IDA.
 * @return  A @c PLUGIN_ constant from loader.hpp.
 */
int idaapi init()
{
    if (!is_idaq()) return PLUGIN_SKIP;
    msg("[" PLUGIN_NAME "] " PLUGIN_TEXTUAL_VERSION " by athre0z (zyantific.com) loaded!\n");

    try
    {
        Core::instance().initPlugin();
    }
    catch (const std::runtime_error &e)
    {
        msg("[" PLUGIN_NAME "][ERROR] Cannot load plugin: %s\n", e.what());
        return PLUGIN_UNL;
    }

    return PLUGIN_KEEP;
}

/**
 * @brief   Run callback for IDA.
 */
#if IDP_INTERFACE_VERSION >= 700
    bool idaapi run(size_t)
#else
    void idaapi run(int)
#endif
{
    Core::instance().runPlugin();
#if IDP_INTERFACE_VERSION >= 700
    return true;
#endif
}

/**
 * @brief   Shutdown callback for IDA.
 */
void idaapi term()
{
    if (Core::isInstantiated())
    {
        Core::instance().shutdownPlugin();
        Core::freeInstance();
    }
}

plugin_t PLUGIN =
{
    IDP_INTERFACE_VERSION,
    PLUGIN_FIX,
    &init,
    &term,
    &run,
    "Advanced IDA skinning",
    "Plugin providing advanced skinning features using Qt stylesheets.",
    PLUGIN_NAME ": Settings",
    "Ctrl-Shift-S"
};

// ============================================================================================= //
