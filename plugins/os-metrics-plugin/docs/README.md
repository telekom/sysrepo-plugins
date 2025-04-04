<h1 align="center">
    OS Metrics Sysrepo Plugin
</h1>

<p align="center">
  <a href="#development">Development</a> •
  <a href="#documentation">Documentation</a> •
  <a href="#support-and-feedback">Support</a> •
  <a href="#how-to-contribute">Contribute</a> •
  <a href="#contributors">Contributors</a> •
  <a href="#licensing">Licensing</a>
</p>

The goal of this project is to create a metrics module and implementation to get more information out of Debian through the NETCONF pipeline.

## About this component

The OS Metrics Module was designed to deliver a decent amount of information about the environment (cpu, memory, filesystem, processes) while also being able to configure usage thresholds used for notifications.

## Development

The full development progress can be found in the [documentation](./DOCUMENTATION.md).

The plugin assumes it's being installed on a Debian system and uses tools like `df`, and the `/proc` structure internally.

## Documentation

The full documentation for the plugin can be found [documentation](./DOCUMENTATION.md).
