import logging.config

import config

logging.config.fileConfig(config.LOG_CONFIG)

from controller.controller import Controller

if __name__ == '__main__':
    controller = Controller()
    controller.connect()
    controller.start()
