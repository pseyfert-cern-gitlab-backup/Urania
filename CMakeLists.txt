CMAKE_MINIMUM_REQUIRED(VERSION 2.8.5)

#---------------------------------------------------------------
# Load macros and functions for Gaudi-based projects
find_package(GaudiProject)
#---------------------------------------------------------------

# GaudiPolicy is needed only for CMT.
set_property(DIRECTORY PROPERTY GAUDI_IGNORE_SUBDIRS GaudiPolicy)

# Declare project name and version
gaudi_project(Urania v4r0)

